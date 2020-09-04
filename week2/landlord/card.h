#ifndef CARD_H
#define CARD_H
#include <QVector>
#include <QJsonArray>

enum CardSuit {DIAMOND, CLUB, HEART, SPADE};
enum CardPoint {THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, TWO, LITTLEJOKER, BIGJOKER};

struct Card {
	CardSuit suit;
	CardPoint point;
	Card() = default;
	Card(const CardSuit &suit, const CardPoint &point);
	Card(const int &x);
	operator int() {
		return suit * 13 + point;
	}
};

class Cards {
	private:
		QVector<Card> cards;
		enum CardShape {SOLO, PAIR, TRIO, TRIO_SOLO, TRIO_PAIR, CHAIN, SISTERS, AIRPLANE, AIRPLANE_SOLO, AIRPLANE_PAIR, FOUR_SOLO, FOUR_PAIR, BOMB};
		int dragonLength;
		CardPoint maxCardPoint;
		CardShape shape;

	public:
		Cards() = default;
		Cards(const QVector<Card>::iterator &l, const QVector<Card>::iterator &r);
		bool empty() const;
		void clear();
		bool getShape();
		QVector<Card> getCards() const;
		void insert(const Card &card);
		void remove(const int &card);
		QJsonArray toJson() const;
		friend bool overwhelm(Cards i, Cards j);
};

#endif // CARD_H
