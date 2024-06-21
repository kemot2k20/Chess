# OPIS KLAS

Klasa Game :

Klasa jest odpowiedzialna za przeprowadzenie rozgrywki i komunikację z użytkownikiem.
metoda Game::gameLoop() jest główną pętlą gry w której za pomocą UI wyświetlana jest aktualna sytuacja na planszy.

KLASA GameHelper :

GameHelper posiada szereg metod z których korzysta klasa Game. 
Na przykład : sprawdzanie czy jest mat, pat, zwracanie wszystkich możliwych ruchów w danej pozycji, sprawdzanie poprawności ruchu.

KLASA Player :

posiada atrybuty takie jak : nazwa gracza, informację czy gracz jest AI, kolor figur gracza

KLASA UI :

Klasa jest odpowiedzialna za wyświetlanie aktualnej pozycji szachowej i pobieranie od użytkownika ruchu w formacie uci.

# INFORMACJE DODATKOWE

- aby wykonać ruch wpisz ruch w formacie uci, np : e2e4
- aby wyjść z gry w polu na wpisanie ruchu wpisz 'quit'
- jeżeli chcesz możesz w main.cpp zmienić tryb gry
- jest dostępnych 5 poziomów trudności bota, które oznaczają jego głębokość, czym mniejsza tym mniej dokładnie gra.
- po więcej informacji zapraszam do README
