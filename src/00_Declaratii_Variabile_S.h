/* Variabile globale folosite de aplicatia de generare a semnalelor. */

static int panelHandle;
int regim;
int stare_led;
int valoare_led;
double Te;
double tk_1, tk;

float yk_1, yk_2, yk_3, yk;
float uk_1, uk_2, uk_3, uk;

double ynouk, ynouk_1, C, T;
float Refk, Refk_1, Refk_2, Refk0;
int sel_ref;
double timp_rampa_tk, timp_sinus_tk, timp_triunghi_tk;
double T_sin, A_sin;
int comutare_Sin, comutare_triunghi;
