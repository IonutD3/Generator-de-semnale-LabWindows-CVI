#include <advanlys.h>
#include "toolbox.h"
#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>
#include "semnale_T_R_S.h"

#include "00_Declaratii_Variabile_S.h"
#include "01_Functionare_A_M_S.h"
#include "02_Functii_Utilitare_S.h"
#include "03_Generare_Semnale_S.h"

double generare_semnal(void);

/* Functia de pornire a aplicatiei LabWindows/CVI. */
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPSTR lpszCmdLine, int nCmdShow)
{
    if (InitCVIRTE(hInstance, 0, 0) == 0)
        return -1;

    if ((panelHandle = LoadPanel(0, "semnale_T_R_S.uir", PANEL)) < 0)
        return -1;

    DisplayPanel(panelHandle);
    RunUserInterface();
    DiscardPanel(panelHandle);

    return 0;
}

/*
 * Initializeaza aplicatia, perioada de esantionare si parametrii impliciti.
 */
int CVICALLBACK start_aplicatie(int panel, int control, int event,
                                void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_COMMIT:
            InsertTextBoxLine(panelHandle, PANEL_TEXTBOX, -1,
                              "Aplicatia a pornit cu succes.");

            /* Perioada de esantionare este de 10 ms. */
            Te = 0.01;
            tk_1 = 0;
            tk = Te;

            /* Valorile anterioare sunt folosite pentru detectarea fazei sinusului. */
            Refk = 0;
            Refk_1 = 0;
            Refk_2 = 0;

            comutare_Sin = 0;
            comutare_triunghi = 0;

            GetCtrlVal(panelHandle, PANEL_A_SINUS, &A_sin);
            GetCtrlVal(panelHandle, PANEL_T_SINUS, &T_sin);

            /* Parametrii pastrati pentru structura initiala a aplicatiei. */
            T = 10;
            C = Te / (Te + T);
            sel_ref = 0;

            /* Dupa pornire, butonul START nu mai poate fi apasat. */
            SetCtrlAttribute(panelHandle, PANEL_OKBUTTON, ATTR_DIMMED, 1);

            /* Porneste timerul la perioada de esantionare stabilita. */
            SetCtrlAttribute(panelHandle, PANEL_TIMER, ATTR_INTERVAL, Te);
            SetCtrlAttribute(panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
            break;
    }

    return 0;
}

/*
 * Executa un pas de calcul la fiecare eveniment al timerului.
 * Semnalul calculat este trimis simultan catre grafic si catre memoria
 * valorilor anterioare necesare urmatorului esantion.
 */
int CVICALLBACK esantionare(int panel, int control, int event,
                            void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_TIMER_TICK:
            functiune_Automat_Manual();

            Refk = generare_semnal();

            PlotLine(panelHandle, PANEL_GRAPH, tk_1, Refk_1,
                     tk, Refk, VAL_RED);

            tk_1 = tk;
            tk=tk+Te;

            Refk_2 = Refk_1;
            Refk_1 = Refk;
            break;
    }

    return 0;
}
