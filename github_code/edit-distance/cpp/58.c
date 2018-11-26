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

/*!
 * \brief cardpair represents a pair of two cards.
 *
 * The cards don't have to be related to each other.
 * This type was defined for convenience and is used to store possible
 * duplicates.
 */
typedef std::pair<QSharedPointer<Card>, QSharedPointer<Card>> cardpair;

/*!
 * \brief The CardsDeck class represents a deck of Cards against humanity.
 *
 * This class can be seen as a representaion of a full cards against humanity
 * game.
 */
class CardsDeck : public QObject {
  Q_OBJECT

 private:
  /*!
   * \brief all cards in this deck
   */
  QList<QSharedPointer<Card>> cards;

  /*!
   * \brief sort indicates whether the deck shall be sorted
   */
  bool sort = false;

  /*!
   * \brief sorted indicates whether the deck is currently sorted
   */
  bool sorted = false;

  /*!
   * \brief sorts the deck when it isn't sorted and it shall be sorted.
   */
  void sortCards();

 public:
  /*!
   * \brief creates a new (empty) deck
   * \param parent QObject. Defaults to nullptr.
   */
  explicit CardsDeck(QObject *parent = nullptr);

  /*!
   * \brief adds a new Card to the deck.
   * \param card to add to the deck
   *
   * Note that the added card is not copied but only a pointer to the card is
   * stored.
   */
  void addCard(QSharedPointer<Card> card);

  /*!
   * \brief returns a list of possible duplicate card text
   * \param threshold a value betwenn 0 and 1 which indicates the maximum
   * distance
   *        between two possible duplicated cards.
   * \return A list of possible card duplicates whitin the deck
   * \sa isPossibleDuplicate(QSharedPointer<Card> card, QSharedPointer<Card>
   * other, double threshold)
   */
  QList<cardpair> getPossibleDuplicates(double threshold);

  /*!
   * \brief creates the LaTeX-representation of the entire deck
   * \return LaTeX-representation of the entire deck
   */
  QStringList toLatex();

  /*!
   * \brief creates the csv-representation of the entire deck
   * \return csv-representation of the entire deck
   */
  QStringList toCsv();

  /*!
   * \brief getSort
   * \return whether this deck shall (or more precisely is) be sorted or not.
   */
  bool getSort() const;

  /*!
   * \brief setSort defines whether the deck shall be sorted.
   * \param value if set to true the deck will be sorted before returning any
   * cards.
   */
  void setSort(bool value);

 signals:

 public slots:
};

/*!
 * \brief calculates the levenshtein-distance betwenn to strings.
 *
 * The levenshtein-distance is used to check whether two cards are possible
 * duplicates
 *
 * \param s1 first string to compare
 * \param s2 second string to compare
 * \return The levenshtein-distance between s1 and s1
 */
int levenshtein_distance(const std::string &s1, const std::string &s2);

/*!
 * \brief returns whether the two given cards are duplicates or not
 * \param card first card to check
 * \param other second card to check
 * \param threshold a value between 0 and 1. A higher value means more cards
 * will be seen as duplicates.
 *        A value of 1 will mark all pairs as duplicate. A value of 0 will mark
 * any pair as duplicate.
 * \return true when the given cards a possible duplicates, false otherwise
 */
bool isPossibleDuplicate(QSharedPointer<Card> card, QSharedPointer<Card> other,
                         double threshold);
}

#endif  // CARDSDECK_H
