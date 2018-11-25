#ifndef CARDSDECK_H
#define CARDSDECK_H

#include <QList>
#include <QObject>
#include <QSharedPointer>
#include <QStringList>
#include <utility>
#include "blackcard.h"
#include "card.h"
#include "whitecard.h"

namespace cah {


typedef std::pair<QSharedPointer<Card>, QSharedPointer<Card>> cardpair;


class CardsDeck : public QObject {
  Q_OBJECT

 private:
  
  QList<QSharedPointer<Card>> cards;

  
  bool sort = false;

  
  bool sorted = false;

  
  void sortCards();

 public:
  
  explicit CardsDeck(QObject *parent = nullptr);

  
  void addCard(QSharedPointer<Card> card);

  
  QList<cardpair> getPossibleDuplicates(double threshold);

  
  QStringList toLatex();

  
  QStringList toCsv();

  
  bool getSort() const;

  
  void setSort(bool value);

 signals:

 public slots:
};


int levenshtein_distance(const std::string &s1, const std::string &s2);


bool isPossibleDuplicate(QSharedPointer<Card> card, QSharedPointer<Card> other,
                         double threshold);
}

#endif  
