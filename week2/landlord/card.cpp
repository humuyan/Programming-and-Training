#include "card.h"
#include <QJsonArray>

Card::Card(const CardSuit &suit, const CardPoint &point) : suit(suit), point(point) {}
Card::Card(const int &x) : suit(CardSuit(std::min(x / 13, int(SPADE)))) {
	if (x < 52) {
		point = CardPoint(x % 13);
	} else {
		point = CardPoint(x - 39);
	}
}

Cards::Cards(const QVector<Card>::iterator &l, const QVector<Card>::iterator &r) {
	for (auto p = l; p != r; ++p) {
		cards.push_back(*p);
	}
}
QVector<Card> Cards::getCards() const {
	return cards;
}
void Cards::insert(const Card &card) {
	cards.push_back(card);
}
void Cards::remove(const int &card) {
	for (auto it = cards.begin(); it != cards.end(); ++it) {
		if (int(*it) == card) {
			cards.erase(it);
			break;
		}
	}
}
bool Cards::empty() const {
	return cards.empty();
}
void Cards::clear() {
	cards.clear();
}
bool Cards::getShape() {
	int h[15];
	memset(h, 0, sizeof(h));
	for (Card x: cards) {
		++h[x.point];
	}
	QVector<CardPoint> a[5];
	for (int i = 0; i < 15; ++i) {
		a[h[i]].push_back(CardPoint(i));
	}
	if (a[1].size() == 1 && a[2].empty() && a[3].empty() && a[4].empty()) {
		shape = SOLO, maxCardPoint = a[1][0];
		return true;
	}
	if (a[2].size() == 1 && a[1].empty() && a[3].empty() && a[4].empty()) {
		shape = PAIR, maxCardPoint = a[2][0];
		return true;
	}
	if (a[3].size() == 1 && a[1].empty() && a[2].empty() && a[4].empty()) {
		shape = TRIO, maxCardPoint = a[3][0];
		return true;
	}
	if (a[3].size() == 1 && a[1].size() == 1 && a[2].empty() && a[4].empty()) {
		shape = TRIO_SOLO, maxCardPoint = a[3][0];
		return true;
	}
	if (a[3].size() == 1 && a[2].size() == 1 && a[1].empty() && a[4].empty()) {
		shape = TRIO_PAIR, maxCardPoint = a[3][0];
		return true;
	}
	if (a[1].size() >= 5 && a[2].empty() && a[3].empty() && a[4].empty()) {
		bool chain = (*a[1].rbegin() <= ACE);
		for (int i = 1; i < a[1].size(); ++i) {
			if (a[1][i] - a[1][i - 1] != 1) {
				chain = false;
				break;
			}
		}
		if (chain) {
			shape = CHAIN, maxCardPoint = *a[1].rbegin(), dragonLength = a[1].size();
			return true;
		}
	}
	if (a[2].size() >= 3 && a[1].empty() && a[3].empty() && a[4].empty()) {
		bool sisters = (*a[2].rbegin() <= ACE);
		for (int i = 1; i < a[2].size(); ++i) {
			if (a[2][i] - a[2][i - 1] != 1) {
				sisters = false;
				break;
			}
		}
		if (sisters) {
			shape = SISTERS, maxCardPoint = *a[2].rbegin(), dragonLength = a[2].size();
			return true;
		}
	}
	if (a[3].size() == 2 && a[1].empty() && a[2].empty() && a[4].empty() && a[3][0] + 1 == a[3][1] && a[3][1] <= ACE) {
		shape = AIRPLANE, maxCardPoint = a[3][1];
		return true;
	}
	if (a[3].size() + a[4].size() == 2) {
		if (a[3].size() == 2) {
			if (a[3][0] + 1 == a[3][1] && a[3][1] <= ACE && a[1].size() + a[2].size() * 2 == 2) {
				shape = AIRPLANE_SOLO, maxCardPoint = a[3][1];
				return true;
			}
		} else {
			CardPoint minPoint = std::min(a[3][0], a[4][0]), maxPoint = std::max(a[3][0], a[4][0]);
			if (minPoint + 1 == maxPoint && maxPoint <= ACE && a[1].size() == 1 && a[2].empty()) {
				shape = AIRPLANE_SOLO, maxCardPoint = maxPoint;
				return true;
			}
		}
	}
	if (a[3].size() == 2 && a[1].empty() && a[2].size() + a[4].size() * 2 == 2 && a[3][0] + 1 == a[3][1] && a[3][1] <= ACE) {
		shape = AIRPLANE_PAIR, maxCardPoint = a[3][1];
		return true;
	}
	if (a[4].size() == 1 && a[1].size() + a[2].size() * 2 == 2 && a[3].empty()) {
		shape = FOUR_SOLO, maxCardPoint = a[4][0];
		return true;
	}
	if (a[1].empty() && a[3].empty() && ((a[4].size() == 2 && a[2].empty()) || (a[4].size() == 1 && a[2].size() == 2))) {
		shape = FOUR_PAIR, maxCardPoint = *a[4].rbegin();
		return true;
	}
	if (a[2].empty() && a[3].empty()) {
		if (a[4].size() == 1 && a[1].empty()) {
			shape = BOMB, maxCardPoint = a[4][0];
			return true;
		}
		if (a[1].size() == 2 && a[1][0] == LITTLEJOKER && a[1][1] == BIGJOKER) {
			shape = BOMB, maxCardPoint = BIGJOKER;
			return true;
		}
	}
	return false;
}
QJsonArray Cards::toJson() const {
	QJsonArray ret;
	for (Card x: cards) {
		ret.append(int(x));
	}
	return ret;
}

bool overwhelm(Cards i, Cards j) {
	if (!i.getShape()) {
		return false;
	}
	if (j.empty()) {
		return true;
	}
	j.getShape();
	if (i.shape != j.shape) {
		return (i.shape == Cards::BOMB);
	}
	if ((i.shape == Cards::CHAIN || i.shape == Cards::SISTERS) && (i.dragonLength != j.dragonLength)) {
		return false;
	}
	return (i.maxCardPoint > j.maxCardPoint);
}
