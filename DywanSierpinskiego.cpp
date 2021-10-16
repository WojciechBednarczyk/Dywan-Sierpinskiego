 

/*************************************************************************************/

// Trochę bardziej skomplikowany program wykorzystujący funkcje biblioteki OpenGL

/*************************************************************************************/ 

#include <windows.h>

#include <gl/gl.h>

#include <gl/glut.h>
#include <iostream>

using namespace std;
/*************************************************************************************/

typedef float point2[2];
point2 lewy_dolny;
point2 prawy_dolny;
point2 lewy_gorny;
point2 prawy_gorny;
float bok_kwadratu=243.0;
int stopien = 7;
int stopien_pom=0;

void losuj_kolory()
{
    glColor3f(float(rand() % 100) / 100.0, float(rand() % 100) / 100.0, float(rand() % 100) / 100.0);
}

void rysuj_kwadrat(point2 wierzch1, point2 wierzch2, point2 wierzch3, point2 wierzch4)
{
    glBegin(GL_POLYGON);
    losuj_kolory();
    glVertex2fv(wierzch1);
    losuj_kolory();
    glVertex2fv(wierzch2);
    losuj_kolory();
    glVertex2fv(wierzch3);
    losuj_kolory();
    glVertex2fv(wierzch4);
    glEnd();
}

void kolejny_kwadrat(float bok,point2 lewy_dolny, point2 lewy_gorny, point2 prawy_gorny, point2 prawy_dolny)
{
    point2 wierzch1;
    point2 wierzch2;
    point2 wierzch3;
    point2 wierzch4;

    wierzch1[0] = lewy_dolny[0];
    wierzch1[1] = lewy_dolny[1];

    wierzch2[0] = lewy_gorny[0];
    wierzch2[1] = lewy_gorny[1];

    wierzch3[0] = prawy_gorny[0];
    wierzch3[1] = prawy_gorny[1];

    wierzch4[0] = prawy_dolny[0];
    wierzch4[1] = prawy_dolny[1];

    wierzch2[0] = wierzch3[0];
    wierzch1[0] = wierzch4[0];
    wierzch3[0] = wierzch2[0] + bok;
    wierzch4[0] = wierzch3[0];
    rysuj_kwadrat(wierzch1, wierzch2, wierzch3, wierzch4);
}
void kolejna_linia(float bok, point2 lewy_dolny, point2 lewy_gorny, point2 prawy_gorny, point2 prawy_dolny)
{
    point2 wierzch1;
    point2 wierzch2;
    point2 wierzch3;
    point2 wierzch4;

    wierzch1[0] = lewy_dolny[0];
    wierzch1[1] = lewy_dolny[1];

    wierzch2[0] = lewy_gorny[0];
    wierzch2[1] = lewy_gorny[1];

    wierzch3[0] = prawy_gorny[0];
    wierzch3[1] = prawy_gorny[1];

    wierzch4[0] = prawy_dolny[0];
    wierzch4[1] = prawy_dolny[1];

    wierzch2[0] -= 2 * bok;
    wierzch2[1] = wierzch1[1];
    wierzch1[0] = wierzch2[0];
    wierzch1[1] = wierzch2[1] - bok;
    wierzch3[0] = wierzch2[0] + bok;
    wierzch3[1] = wierzch2[1];
    wierzch4[0] = wierzch3[0];
    wierzch4[1] = wierzch1[1];
    rysuj_kwadrat(wierzch1, wierzch2, wierzch3, wierzch4);
}
void podziel(float bok_kwadratu, point2 lewy_dolny, point2 lewy_gorny, point2 prawy_gorny, point2 prawy_dolny,int stopien_pom)
{
    point2 wierzch1;
    point2 wierzch2;
    point2 wierzch3;
    point2 wierzch4;
    float bok = bok_kwadratu;
    wierzch1[0] = lewy_dolny[0];
    wierzch1[1] = lewy_dolny[1];

    wierzch2[0] = lewy_gorny[0];
    wierzch2[1] = lewy_gorny[1];

    wierzch3[0] = prawy_gorny[0];
    wierzch3[1] = prawy_gorny[1];

    wierzch4[0] = prawy_dolny[0];
    wierzch4[1] = prawy_dolny[1];
    if (stopien_pom != stopien)
    {
        //1 kwadrat
        //lewy_gorny bez zmian
        bok /= 3.0;

        wierzch1[1] = wierzch2[1] - bok;
        wierzch3[0] = wierzch2[0] + bok;
        wierzch4[0] = wierzch2[0] + bok;
        wierzch4[1] = wierzch1[1];
        rysuj_kwadrat(wierzch1, wierzch2, wierzch3, wierzch4);
        stopien_pom++;
        podziel(bok, wierzch1, wierzch2, wierzch3, wierzch4, stopien_pom);
    }




    //2 kwadrat
    kolejny_kwadrat(bok, wierzch1, wierzch2, wierzch3, wierzch4);
    wierzch2[0] = wierzch3[0];
    wierzch1[0] = wierzch4[0];
    wierzch3[0] = wierzch2[0] + bok;
    wierzch4[0] = wierzch3[0];
    if (stopien_pom != stopien)
    {
        podziel(bok, wierzch1, wierzch2, wierzch3, wierzch4, stopien_pom);
    }
    //3 kwadrat
    kolejny_kwadrat(bok, wierzch1, wierzch2, wierzch3, wierzch4);
    wierzch2[0] = wierzch3[0];
    wierzch1[0] = wierzch4[0];
    wierzch3[0] = wierzch2[0] + bok;
    wierzch4[0] = wierzch3[0];
    if (stopien_pom != stopien)
    {
        podziel(bok, wierzch1, wierzch2, wierzch3, wierzch4, stopien_pom);
    }

    //4 kwadrat
    kolejna_linia(bok, wierzch1, wierzch2, wierzch3, wierzch4);
    wierzch2[0] -= 2 * bok;
    wierzch2[1] = wierzch1[1];
    wierzch1[0] = wierzch2[0];
    wierzch1[1] = wierzch2[1] - bok;
    wierzch3[0] = wierzch2[0] + bok;
    wierzch3[1] = wierzch2[1];
    wierzch4[0] = wierzch3[0];
    wierzch4[1] = wierzch1[1];
    if (stopien_pom != stopien)
    {
        podziel(bok, wierzch1, wierzch2, wierzch3, wierzch4, stopien_pom);
    }

    //5 kwadrat pusty!

    wierzch2[0] = wierzch3[0];
    wierzch1[0] = wierzch4[0];
    wierzch3[0] = wierzch2[0] + bok;
    wierzch4[0] = wierzch3[0];
    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2fv(wierzch1);
    glVertex2fv(wierzch2);
    glVertex2fv(wierzch3);
    glVertex2fv(wierzch4);
    glEnd();

    //6 kwadrat
    kolejny_kwadrat(bok, wierzch1, wierzch2, wierzch3, wierzch4);
    wierzch2[0] = wierzch3[0];
    wierzch1[0] = wierzch4[0];
    wierzch3[0] = wierzch2[0] + bok;
    wierzch4[0] = wierzch3[0];
    if (stopien_pom != stopien)
    {
        podziel(bok, wierzch1, wierzch2, wierzch3, wierzch4, stopien_pom);
    }

    //7 kwadrat
    kolejna_linia(bok, wierzch1, wierzch2, wierzch3, wierzch4);
    wierzch2[0] -= 2 * bok;
    wierzch2[1] = wierzch1[1];
    wierzch1[0] = wierzch2[0];
    wierzch1[1] = wierzch2[1] - bok;
    wierzch3[0] = wierzch2[0] + bok;
    wierzch3[1] = wierzch2[1];
    wierzch4[0] = wierzch3[0];
    wierzch4[1] = wierzch1[1];
    if (stopien_pom != stopien)
    {
        podziel(bok, wierzch1, wierzch2, wierzch3, wierzch4, stopien_pom);
    }

    ////8 kwadrat
    kolejny_kwadrat(bok, wierzch1, wierzch2, wierzch3, wierzch4);
    wierzch2[0] = wierzch3[0];
    wierzch1[0] = wierzch4[0];
    wierzch3[0] = wierzch2[0] + bok;
    wierzch4[0] = wierzch3[0];
    if (stopien_pom != stopien)
    {
        podziel(bok, wierzch1, wierzch2, wierzch3, wierzch4, stopien_pom);
    }

    ////9 kwadrat
    kolejny_kwadrat(bok, wierzch1, wierzch2, wierzch3, wierzch4);
    wierzch2[0] = wierzch3[0];
    wierzch1[0] = wierzch4[0];
    wierzch3[0] = wierzch2[0] + bok;
    wierzch4[0] = wierzch3[0];
    if (stopien_pom != stopien)
    {
        podziel(bok, wierzch1, wierzch2, wierzch3, wierzch4, stopien_pom);
    }

}
void dywan_sierpinskiego()
{

    //ustalanie wspolrzednych pierwszego kwadratu
    lewy_dolny[0] = -(bok_kwadratu / 2.0);
    lewy_dolny[1] = -(bok_kwadratu / 2.0);
    lewy_gorny[0] = -(bok_kwadratu / 2.0);
    lewy_gorny[1] = (bok_kwadratu / 2.0);
    prawy_dolny[0] = bok_kwadratu / 2.0;
    prawy_dolny[1] = -(bok_kwadratu / 2.0);
    prawy_gorny[0] = bok_kwadratu / 2.0;
    prawy_gorny[1] = bok_kwadratu / 2.0;

    glClear(GL_COLOR_BUFFER_BIT);
    // Czyszczenie okna aktualnym kolorem czyszczącym

    //rysuje glowny kwadrat
    rysuj_kwadrat(lewy_dolny, lewy_gorny, prawy_gorny, prawy_dolny);

    podziel(bok_kwadratu, lewy_dolny, lewy_gorny, prawy_gorny, prawy_dolny,stopien_pom);
    
}

// Funkcaja określająca, co ma być rysowane
// (zawsze wywoływana, gdy trzeba przerysować scenę)


 

void RenderScene(void)
{
    
    dywan_sierpinskiego();
    glFlush();
    // Przekazanie poleceń rysujących do wykonania

}

/*************************************************************************************/

// Funkcja ustalająca stan renderowania

 

void MyInit(void)

{

   glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
   // Kolor okna wnętrza okna - ustawiono na szary

}

/*************************************************************************************/

// Funkcja służąca do kontroli zachowania proporcji rysowanych obiektów
// niezależnie od rozmiarów okna graficznego



void ChangeSize(GLsizei horizontal, GLsizei vertical)

// Parametry horizontal i vertical (szerokość i wysokość okna) są
// przekazywane do funkcji za każdym razem, gdy zmieni się rozmiar okna

{

     GLfloat AspectRatio;

     // Deklaracja zmiennej AspectRatio określającej proporcję wymiarów okna

 

    if(vertical==0)
    // Zabezpieczenie pzred dzieleniem przez 0

        vertical = 1;

     glViewport(0, 0, horizontal, vertical);
     // Ustawienie wielkościokna okna urządzenia (Viewport)
     // W tym przypadku od (0,0) do (horizontal, vertical)

    glMatrixMode(GL_PROJECTION); 
    // Określenie układu współrzędnych obserwatora

    glLoadIdentity();
    // Określenie przestrzeni ograniczającej

    AspectRatio = (GLfloat)horizontal/(GLfloat)vertical;
    // Wyznaczenie współczynnika proporcji okna

    // Gdy okno na ekranie nie jest kwadratem wymagane jest
    // określenie okna obserwatora.
    // Pozwala to zachować właściwe proporcje rysowanego obiektu
    // Do określenia okna obserwatora służy funkcja glOrtho(...)

 

    if(horizontal <= vertical)

    glOrtho(-150.0,150.0,-150.0/AspectRatio,150.0/AspectRatio,1.0,-1.0); 

     else

    glOrtho(-150.0*AspectRatio,150.0*AspectRatio,-150.0,150.0,1.0,-1.0); 

    glMatrixMode(GL_MODELVIEW);
    // Określenie układu współrzędnych     

    glLoadIdentity();

}

/*************************************************************************************/

// Główny punkt wejścia programu. Program działa w trybie konsoli

 

void main(void)

{

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
   // Ustawienie trybu wyświetlania
   // GLUT_SINGLE - pojedynczy bufor wyświetlania
   // GLUT_RGBA - model kolorów RGB

 

   glutCreateWindow("Dywan Sierpinskiego");
   // Utworzenie okna i określenie treści napisu w nagłówku okna

   glutDisplayFunc(RenderScene);
   // Określenie, że funkcja RenderScene będzie funkcją zwrotną (callback)
   // Biblioteka GLUT będzie wywoływała tą funkcję za każdym razem, gdy
   // trzeba będzie przerysować okno


   glutReshapeFunc(ChangeSize);
   // Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną za
   // zmiany rozmiaru okna

   MyInit();
   // Funkcja MyInit (zdefiniowana powyżej) wykonuje wszelkie 
   // inicjalizacje konieczneprzed przystąpieniem do renderowania


   glutMainLoop();
   // Funkcja uruchamia szkielet biblioteki GLUT

}

/*************************************************************************************/