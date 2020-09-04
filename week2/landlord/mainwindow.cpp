#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "card.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QPainter>
#include <QMouseEvent>

int MainWindow::UICard::height = 0;
int MainWindow::UICard::width = 0;
MainWindow::UICard::UICard(const Card &base) : Card(base) {
	QString name;
	switch (point) {
		case LITTLEJOKER: name = "LITTLEJOKER"; break;
		case BIGJOKER: name = "BIGJOKER"; break;
		default: name = "DCHS"[suit] + QString::number(point <= KING ? point + 3 : point - 10); break;
	}
	fileName = ":/cardpic/" + name + ".png";
	image = QImage(fileName).scaled(width, height);
	up = false;
}

void MainWindow::sendMessage(const QJsonObject &info) {
	clientSocket->sendBinaryMessage(QJsonDocument(info).toJson());
}
void MainWindow::updateRest() {
	ui->leftRestLabel->setText("剩余" + QString::number(leftRest) + "张");
	ui->rightRestLabel->setText("剩余" + QString::number(rightRest) + "张");
	ui->myRestLabel->setText("剩余" + QString::number(cards.size()) + "张");
}
template<class T>
void MainWindow::sortCards(QVector<T> &cards) {
	std::sort(cards.begin(), cards.end(), [](const T &i, const T &j){return ((i.point > j.point) || (i.point == j.point && i.suit > j.suit));});
}
void MainWindow::resizeEvent(QResizeEvent*) {
	ui->startButton->move(width() - ui->startButton->width(), 0);
	ui->exitButton->move(width() - ui->exitButton->width(), ui->startButton->height());
	if (height() / 4.0 / 29 < width() / 24.0 * 5 / 21) {
		UICard::height = height() / 5.0, UICard::width = UICard::height / 29.0 * 21;
	} else {
		UICard::width = width() / 24.0 * 5, UICard::height = UICard::width / 21.0 * 29;
	}
	Padding.image = QImage(Padding.fileName).scaled(UICard::width, UICard::height);
	if (showLandlordCards) {
		for (UICard &card: landlordCards) {
			card.image = QImage(card.fileName).scaled(UICard::width, UICard::height);
		}
	}
	for (UICard &card: cards) {
		card.image = QImage(card.fileName).scaled(UICard::width, UICard::height);
	}
	for (UICard &card: centralCards) {
		card.image = QImage(card.fileName).scaled(UICard::width, UICard::height);
	}
	ui->callLandlordButton->move((width() - ui->callLandlordButton->width() * 3) / 2, height() - UICard::height - ui->callLandlordButton->height() - 20);
	ui->noCallButton->move((width() - ui->noCallButton->width() * 3) / 2 + ui->noCallButton->width() * 2, height() - UICard::height - ui->noCallButton->height() - 20);
	ui->playButton->move((width() - ui->playButton->width() * 3) / 2, height() - UICard::height * 1.2 - ui->playButton->height() - 20);
	ui->noPlayButton->move((width() - ui->noPlayButton->width() * 3) / 2 + ui->noPlayButton->width() * 2, height() - UICard::height * 1.2 - ui->noPlayButton->height() - 20);
	ui->myLabel->move((width() - ui->myLabel->width()) / 2, height() - UICard::height - ui->myLabel->height() - 30);
	ui->leftLabel->move(UICard::width + 20, (height() - ui->leftLabel->height()) / 2);
	ui->rightLabel->move(width() - UICard::width - ui->rightLabel->width() - 20, (height() - ui->leftLabel->height()) / 2);
	ui->leftRestLabel->move(10 + (UICard::width - ui->leftRestLabel->width()) / 2, (height() - UICard::height) / 2 + UICard::height + 10);
	ui->rightRestLabel->move(width() - 10 - (UICard::width - ui->rightRestLabel->width()) / 2 - ui->rightRestLabel->width(), (height() - UICard::height) / 2 + UICard::height + 10);
	ui->leftIdentityLabel->move(10 + (UICard::width - ui->leftIdentityLabel->width()) / 2, (height() - UICard::height) / 2 - ui->leftIdentityLabel->height() - 10);
	ui->rightIdentityLabel->move(width() - 10 - (UICard::width - ui->rightIdentityLabel->width()) / 2 - ui->rightIdentityLabel->width(), (height() - UICard::height) / 2 - ui->rightIdentityLabel->height() - 10);
	ui->restartButton->move((width() - ui->restartButton->width()) / 2, height() - UICard::height - ui->restartButton->height() - 20);
	ui->myRestLabel->move(width() - ui->myRestLabel->width() - 10, height() - ui->myRestLabel->height() - 10);
	ui->myIdentityLabel->move(width() - ui->myIdentityLabel->width() - 10, height() - ui->myRestLabel->height() - ui->myIdentityLabel->height() - 20);
}
void MainWindow::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	painter.setBrush(Qt::white), painter.fillRect(0, 0, width(), height(), painter.brush());
	int offsetX = (width() - 3 * UICard::width) / 2;
	if (dealt) {
		for (int i = 0; i < 3; ++i) {
			painter.drawImage(offsetX + i * UICard::width, 0, showLandlordCards ? landlordCards[i].image : Padding.image);
		}
		painter.drawImage(10, (height() - UICard::height) / 2, Padding.image);
		painter.drawImage(width() - UICard::width - 10, (height() - UICard::height) / 2, Padding.image);
	}
	offsetX = (width() - (cards.size() + 4) / 5.0 * UICard::width) / 2;
	for (int i = 0; i < cards.size(); ++i) {
		painter.drawImage(offsetX + i * UICard::width / 5.0, height() - UICard::height * (cards[i].up ? 1.2 : 1) - 10, cards[i].image);
	}
	offsetX = (width() - (centralCards.size() + 4) / 5.0 * UICard::width) / 2;
	for (int i = 0; i < centralCards.size(); ++i) {
		painter.drawImage(offsetX + i * UICard::width / 5.0, (height() - UICard::height) / 2, centralCards[i].image);
	}
}
void MainWindow::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton && playing) {
		int offsetX = (width() - (cards.size() + 4) / 5.0 * UICard::width) / 2;
		if (e->x() >= offsetX && e->x() <= offsetX + (cards.size() + 4) * UICard::width / 5) {
			int i = std::min<int>((e->x() - offsetX) * 5.0 / UICard::width, cards.size() - 1), offsetY = height() - UICard::height * (cards[i].up ? 1.2 : 1) - 10;
			if (e->y() >= offsetY && e->y() <= offsetY + UICard::height) {
				if (cards[i].up) {
					cards[i].up = false;
					chosenCards.remove(int(cards[i]));
				} else {
					cards[i].up = true;
					chosenCards.insert(cards[i]);
				}
				update();
			}
		}
	}
}
void MainWindow::init() {
	ui->myLabel->hide(), ui->myIdentityLabel->hide(), ui->myRestLabel->hide();
	ui->leftLabel->hide(), ui->rightLabel->hide(), ui->leftRestLabel->hide(), ui->rightRestLabel->hide(), ui->leftIdentityLabel->hide(), ui->rightIdentityLabel->hide();
	ui->callLandlordButton->hide(), ui->noCallButton->hide(), ui->playButton->hide(), ui->noPlayButton->hide(), ui->restartButton->hide();
	cards.clear(), centralCards.clear(), lastPlay.clear();
	dealt = showLandlordCards = playing = firstDisabled = false;
	noPlayCount = 0;
}
void MainWindow::callLandlord(const bool &called) {
	QJsonObject sendInfo = initMessage(CALL_LANDLORD);
	sendInfo.insert("clientID", id);
	sendInfo.insert("called", called);
	sendInfo.insert("sbCalled", ui->callLandlordButton->text() == CallButtonName[1][1]);
	sendMessage(sendInfo);
	ui->myLabel->setText(called ? ui->callLandlordButton->text() : ui->noCallButton->text());
	ui->callLandlordButton->hide(), ui->noCallButton->hide(), ui->myLabel->show();
}

void MainWindow::processMessage(QByteArray msg) {
	QJsonObject info = QJsonDocument::fromJson(msg).object();
	QJsonArray cardArray;
	switch (info["messageType"].toInt()) {
		case SEND_ID:
			id = info["ID"].toInt();
			setWindowTitle(QString::number(id));
			break;
		case DEAL:
			dealt = true;
			cardArray = info["cards"].toArray();
			cards.clear();
			for (QJsonValue x: cardArray) {
				cards.push_back(Card(x.toInt()));
			}
			sortCards(cards), update();
			cardArray = info["landlordCards"].toArray();
			for (int i = 0; i < 3; ++i) {
				landlordCards[i] = Card(cardArray.at(i).toInt());
			}
			leftRest = rightRest = 17;
			break;
		case CALL_LANDLORD:
			ui->noCallButton->setText(CallButtonName[0][info["sbCalled"].toBool()]);
			ui->callLandlordButton->setText(CallButtonName[1][info["sbCalled"].toBool()]);
			ui->callLandlordButton->show(), ui->noCallButton->show();
			break;
		case CALL_STATUS_UPDATE:
			if (info["ID"].toInt() == (id + 1) % MaxPlayers) {
				ui->rightLabel->setText(CallButtonName[info["called"].toBool()][info["sbCalled"].toBool()]);
				ui->rightLabel->show();
			} else if (info["ID"].toInt() != id) {
				ui->leftLabel->setText(CallButtonName[info["called"].toBool()][info["sbCalled"].toBool()]);
				ui->leftLabel->show();
			}
			break;
		case LANDLORD:
			ui->leftIdentityLabel->setText("农民"), ui->rightIdentityLabel->setText("农民"), ui->myIdentityLabel->setText("农民");
			if (info["ID"].toInt() == id) {
				cards.push_back(landlordCards[0]), cards.push_back(landlordCards[1]), cards.push_back(landlordCards[2]), sortCards(cards);
				ui->myIdentityLabel->setText("地主");
				firstDisabled = true;
			} else {
				if (info["ID"].toInt() == (id + 1) % MaxPlayers) {
					rightRest += 3, ui->rightIdentityLabel->setText("地主");
				} else {
					leftRest += 3, ui->leftIdentityLabel->setText("地主");
				}
			}
			showLandlordCards = true, update();
			ui->myLabel->hide(), ui->leftLabel->hide(), ui->rightLabel->hide();
			ui->myRestLabel->show(), ui->leftRestLabel->show(), ui->rightRestLabel->show(), updateRest();
			ui->myIdentityLabel->show(), ui->leftIdentityLabel->show(), ui->rightIdentityLabel->show();
			break;
		case PLAY:
			if (firstDisabled) {
				ui->noPlayButton->setEnabled(false);
				firstDisabled = false;
			} else {
				ui->noPlayButton->setEnabled(noPlayCount < 2);
			}
			if (noPlayCount == 2) {
				lastPlay.clear();
			}
			ui->myLabel->hide(), ui->playButton->show(), ui->noPlayButton->show();
			playing = true;
			break;
		case PLAY_STATUS_UPDATE:
			cardArray = info["cards"].toArray();
			if (info["ID"].toInt() == id) {
				ui->playButton->hide(), ui->noPlayButton->hide();
				ui->rightLabel->hide();
			} else if (info["ID"].toInt() == (id + 1) % MaxPlayers) {
				ui->leftLabel->hide();
			} else {
				ui->myLabel->hide();
			}
			if (cardArray.empty()) {
				if (info["ID"].toInt() == id) {
					ui->myLabel->setText("不出"), ui->myLabel->show();
				} else if (info["ID"].toInt() == (id + 1) % MaxPlayers) {
					ui->rightLabel->setText("不出"), ui->rightLabel->show();
				} else {
					ui->leftLabel->setText("不出"), ui->leftLabel->show();
				}
				++noPlayCount;
			} else {
				centralCards.clear();
				for (QJsonValue x: cardArray) {
					centralCards.push_back(Card(x.toInt()));
				}
				sortCards(centralCards);
				lastPlay.clear();
				for (UICard x: centralCards) {
					lastPlay.insert(x);
				}
				if (noPlayCount == 2) {
					ui->myLabel->hide(), ui->leftLabel->hide(), ui->rightLabel->hide();
				}
				noPlayCount = 0;
				if (info["ID"].toInt() == (id + 1) % MaxPlayers) {
					rightRest -= cardArray.size(), updateRest();
				} else if (info["ID"].toInt() != id) {
					leftRest -= cardArray.size(), updateRest();
				}
			}
			update();
			break;
		case GAME_OVER:
			if (info["win"].toBool()) {
				QMessageBox::information(nullptr, "You win", "你赢了！");
			} else {
				QMessageBox::information(nullptr, "You lose", "你输了！");
			}
			ui->restartButton->setEnabled(true), ui->restartButton->show();
			break;
		case RESTART:
			init();
			break;
	}
}
void MainWindow::serverConnected() {
	disconnect(clientSocket, SIGNAL(connected()), this, SLOT(serverConnected()));
	disconnect(clientSocket, SIGNAL(disconnected()), this, SLOT(establishServer()));
	QMessageBox::information(nullptr, "Connected", "连接成功！");
	ui->startButton->setEnabled(false);
}
void MainWindow::establishServer() {
	server = new Server;
	clientSocket->open(ServerUrl);
}
void MainWindow::on_startButton_clicked() {
	clientSocket->open(ServerUrl);
}
void MainWindow::on_playButton_clicked() {
	if (overwhelm(chosenCards, lastPlay)) {
		QVector<Card> chosenList = chosenCards.getCards();
		sortCards(chosenList);
		QVector<UICard> oldCards = cards;
		cards.clear();
		for (int i = 0, j = 0; i < oldCards.size(); ++i) {
			if (j >= chosenList.size() || int(oldCards[i]) != int(chosenList[j])) {
				cards.push_back(oldCards[i]);
			} else {
				++j;
			}
		}
		updateRest(), update();
		QJsonObject sendInfo = initMessage(PLAY);
		sendInfo.insert("clientID", id);
		sendInfo.insert("cards", chosenCards.toJson());
		sendInfo.insert("finished", cards.empty());
		sendMessage(sendInfo);
		chosenCards.clear();
		playing = false;
	} else {
		QMessageBox::information(nullptr, "Hint", "牌型不合法！");
	}
}
void MainWindow::on_noPlayButton_clicked() {
	chosenCards.clear();
	for (UICard &card: cards) {
		card.up = false;
	}
	QJsonObject sendInfo = initMessage(PLAY);
	sendInfo.insert("clientID", id);
	sendInfo.insert("cards", Cards().toJson());
	sendInfo.insert("finished", false);
	sendMessage(sendInfo);
	playing = false;
}
void MainWindow::on_restartButton_clicked() {
	QJsonObject sendInfo = initMessage(RESTART);
	sendInfo.insert("clientID", id);
	sendMessage(sendInfo);
	ui->restartButton->setEnabled(false);
}
void MainWindow::on_callLandlordButton_clicked() { callLandlord(true); }
void MainWindow::on_noCallButton_clicked() { callLandlord(false); }
void MainWindow::on_exitButton_clicked() { close(); }

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	srand(time(nullptr));
	server = nullptr, clientSocket = new QWebSocket;
	connect(clientSocket, SIGNAL(connected()), this, SLOT(serverConnected()));
	connect(clientSocket, SIGNAL(disconnected()), this, SLOT(establishServer()));
	connect(clientSocket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(processMessage(QByteArray)));
	Padding.fileName = ":/cardpic/PADDING.png";
	Padding.image = QImage(Padding.fileName).scaled(UICard::width, UICard::height);
	init();
}
MainWindow::~MainWindow() {
	delete ui;
	clientSocket->deleteLater();
	if (server != nullptr) {
		delete server;
	}
}
