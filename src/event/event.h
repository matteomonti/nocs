// Foward declarations

class event;

#if !defined(__forward__) && !defined(__nobb__event__event__h)
#define __nobb__event__event__h

// Libraries

#include <iostream>
#include <cmath>

/*NOTE :: la classe event è la base astratta dell'intero meccanismo di integrazione per eventi. Questo significa che deve contemplare la scrittura coerente di ogni possibile avventimento interno al sistema fisico. Deve pertanto riusltare, alla base, collocabile all'interno dell'albero di eventi che consentira il filtraggio e la classificazione degli avvenimenti in tempo e versione.
  Se cerchiamo di tenere sotto traccia tutto quello che si deve avere:
    -> una variabile booleana che permetta di dire da subito se l'evento costruito ha una minima probabilità di avvenire (in caso negativo si butta via l'oggetto appena costruito).
        ->>> sarà il costruttore delle altre classi a fare questa prima valutazione
    -> una funzione astratta compute() che integri gli elementi in gioco????
    -> un tracciatore temporale che classifichi il momento esatto in cui l'evento avviene (per eseguire poi la collocazione nell'albero di eventi)
    -> una funzione di tracciamento della versione delle molecole in gioco, in modo che sia possibile subito buttare via l'evento qualora, al momento temporale del suo avventimento, la versione delle molecole è cambiato.
*/

class event
{
protected:

  // Protected Members

  bool _happens;
  double _time;

public:

  // Constructors

  event();

  // Getters

  bool happens();
  double time();

  // Public Methods

  virtual void compute();
  virtual bool version_control();
};

#endif
