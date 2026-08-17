/**************************************************************************/
/* Fisier de includere generat pentru resursa de interfata LabWindows/CVI (UIR)              */
/*                                                                        */
/* ATENTIE: acest fisier este generat de LabWindows/CVI.                */
/* Modificarile interfetei trebuie facute in fisierul .uir.             */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panouri si controale ale interfetei. */

#define  PANEL                            1
#define  PANEL_OKBUTTON_2                 2       /* tip: comanda; callback: stergere_grafice */
#define  PANEL_OKBUTTON                   3       /* tip: comanda; callback: start_aplicatie */
#define  PANEL_QUITBUTTON                 4       /* tip: comanda; callback: QuitCallback */
#define  PANEL_TEXTBOX                    5       /* tip: caseta de text; fara callback */
#define  PANEL_LED                        6       /* tip: LED; fara callback */
#define  PANEL_BINARYSWITCH               7       /* tip: comutator binar; fara callback */
#define  PANEL_BINARYSWITCH_2             8       /* tip: comutator binar; fara callback */
#define  PANEL_GRAPH                      9       /* tip: grafic; fara callback */
#define  PANEL_SEL_REF                    10      /* tip: glisor; callback: selectie_semnal */
#define  PANEL_REFERINTA                  11      /* tip: scala; fara callback */
#define  PANEL_T_SINUS                    12      /* tip: numeric; callback: detectare_comutare_SIN */
#define  PANEL_A_SINUS                    13      /* tip: numeric; callback: detectare_comutare_SIN */
#define  PANEL_M_PANTA                    14      /* tip: numeric; callback: modificare_Panta */
#define  PANEL_TIMER                      15      /* tip: timer; callback: esantionare */
#define  PANEL_DECORATION                 16      /* tip: decoratie; fara callback */
#define  PANEL_DECORATION_3               17      /* tip: decoratie; fara callback */
#define  PANEL_TEXTMSG_2                  18      /* tip: mesaj text; fara callback */
#define  PANEL_TEXTMSG                    19      /* tip: mesaj text; fara callback */
#define  PANEL_PERIOADA                   20      /* tip: numeric; callback: semnal_triunghiular */
#define  PANEL_INALTIME                   21      /* tip: numeric; callback: semnal_triunghiular */


     /* Tablouri de controale. */

          /* Nu exista tablouri de controale. */


     /* Bare de meniu, meniuri si elemente de meniu. */

          /* Nu exista bare de meniu. */


     /* Prototipurile functiilor callback. */

int  CVICALLBACK detectare_comutare_SIN(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK esantionare(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK modificare_Panta(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK selectie_semnal(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK semnal_triunghiular(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK start_aplicatie(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK stergere_grafice(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif