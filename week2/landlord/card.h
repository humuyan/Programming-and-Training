#ifndef CARD_H
#define CARD_H
#include <QVector>
#include <QJsonArray>

enum CardSuit {DIAMOND, CLUB, HEART, SPADE};
enum CardPoint {THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, TWO, JOKER, LITTLEJOKER, BIGJOKER};

struct Card {
	CardSuit suit;
	CardPoint point;
	Card() = default;
	Card(const CardSuit &suit, const CardPoint &point);
};

class Cards {
	private:
		QVector<Card> cards;
		enum CardShape {SOLO, PAIR, TRIO, TRIO_SOLO, TRIO_PAIR, CHAIN, SISTERS, AIRPLANE, AIRPLANE_SOLO, AIRPLANE_PAIR, FOUR_SOLO, FOUR_PAIR, BOMB};
		int dragonLength;
		CardPoint maxCardPoint;
		CardShape shape;
		bool getShape();

	public:
		Cards() = default;
		Cards(const QVector<Card>::iterator &l, const QVector<Card>::iterator &r);
		void insert(const Card &card);
		friend bool overwhelm(Cards i, Cards j);
		QJsonArray toJson();
};

#endif // CARD_H
