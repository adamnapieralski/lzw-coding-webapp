# lzw-text-compression-webapp
Projekt dodatkowy realizowany na przedmiot Zaawansowane Programowanie w C++ (ZPR). Minimalistyczna aplikacja webowa realizująca kodowanie i odkodowywanie (kompresję) z wykorzystaniem algorytmu [LZW Lempel-Ziv-Welch](https://pl.wikipedia.org/wiki/LZW).<br>

Aplikacja webowa w architekturze opartej na:
- C++, boost.python - obsługa obliczeniowa,
- Django (Python) - obsługa strony serwera,
- AngularJS + HTML5 - obsługa strony klienta, GUI w przeglądarce.
<br>
Autor: Adam Napieralski.
Wyświetl w języku: [Angielskim](README.md)

## Instalacja

### Wymagania
Biblioteki i używane technologie:
- g++
- scons
- boost (Boost.Python, Boost.Test)
- python3 / python2
- nodejs >=v10.15
- django >=v1.11
- angularjs >=v1.7

### Na Linuxie (tworzone i testowane na Ubuntu 18.04)
Aby zainstalować wszystkie potrzebne pakiety i biblioteki, użyj skryptu:
```
./install.sh
```
Domyślna wersja Pythona przy takiej instalacji to 3.x, jednak możliwe jest wybór python2 przy pomocy argumentu: 
```
./install.sh python=2.6
```
### Na Windowsie
1. Zainstaluj Microsoft Visual Studio.
2. Zainstaluj preferowanego [Pythona](https://www.python.org/download/releases/) (np. Python3.6) w domyślnej ścieżce (C:\Python36\), następnie dodaj ją do zmiennej środowiskowej PATH.
3. Zainstaluj pip / pip3 - pobierz [get-pip.py](https://bootstrap.pypa.io/get-pip.py) i uruchom `python get-pip.py`.
4. `pip install --egg scons`
5. `pip install -r pip_requirements.txt`
6. Pobierz i zainstaluj [boost](http://www.boost.org) w C:\Boost\.
7. Zainstaluj [nodejs](http://nodejs.org/download/)
8. W folderze `client/` zainstaluj moduły JS: `npm install`.

## Budowanie
Aby skompilować i zbudować pełną aplikację użyj:
```
scons
```
Domyślna wersja Pythona w tym procesie to 3.6. By użyć innej wersji spośród wspieranych [2.6, 2.7, 3.6, 3.7, 3.8], dodaj argument:
```
scons python=2.6
```
Raz zdefiniowana, wersja pythona jest zapisana i wykorzystywana przy kolejnych uruchomieniach scons, bez potrzeby ponownego wpisywania.
## Testy
Wykonaj testy jednostkowe po zbudowaniu aplikacji przy pomocy:
```
scons --test
```
## Uruchom serwer
Aby uruchomić serwer django na domyślnym adresie (127.0.0.1:8000), użyj:
```
scons --run
```
lub manualnie: `python ./build_web/manage.py runserver [ip]:[port]` or `python3 ./build_web/manage.py runserver [ip]:[port]`
## Użytkowanie
Otwórz przeglądarkę i przejdź pod zdefiniowany wcześniej adres: http://127.0.0.1:8000/. W lewym oknie tekstowym możesz wpisać tekst do zakodowania lub kod do odkodowania - w zależności od trybu pracy wybranego z użyciem przełącznika. Dodatkowo możliwy jest wybór bitowej wielkości kodu. Wykonaj przetwarzanie z użyciem algorymu naciskając przycisk RUN. Wyświetlony zostanie osiągnięty stopień kompresji.
