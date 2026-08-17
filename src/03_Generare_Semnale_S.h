/*
 * Genereaza cele patru semnale ale aplicatiei:
 * treapta, rampa, sinusoidal si triunghiular.
 *
 * La schimbarea tipului de semnal, semnalele continue pornesc de la valoarea
 * curenta Refk pentru a evita salturile artificiale la momentul comutarii.
 */
double generare_semnal(void)
{
    double local_Refk = 0.0;
    double local_m = 0.0;
    double local_n = 0.0;
    double local_p = 0.0;

    switch (sel_ref)
    {
        case 0:
            /* Semnal treapta: valoarea este citita direct din interfata. */
            SetCtrlAttribute(panelHandle, PANEL_REFERINTA, ATTR_VISIBLE, 1);
            SetCtrlAttribute(panelHandle, PANEL_M_PANTA, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_A_SINUS, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_T_SINUS, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_INALTIME, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_PERIOADA, ATTR_VISIBLE, 0);

            GetCtrlVal(panelHandle, PANEL_REFERINTA, &local_Refk);
            break;

        case 1:
            /*
             * Semnal rampa: porneste din Refk0, adica din valoarea semnalului
             * existenta in momentul selectarii rampei.
             */
            SetCtrlAttribute(panelHandle, PANEL_REFERINTA, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_M_PANTA, ATTR_VISIBLE, 1);
            SetCtrlAttribute(panelHandle, PANEL_A_SINUS, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_T_SINUS, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_INALTIME, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_PERIOADA, ATTR_VISIBLE, 0);

            GetCtrlVal(panelHandle, PANEL_M_PANTA, &local_m);
            local_n=Refk0;
	    local_Refk=local_m*timp_rampa_tk+local_n;
	    timp_rampa_tk=timp_rampa_tk+Te;
            break;

        case 2:
            /*
             * Semnal sinusoidal: amplitudinea si perioada sunt citite din
             * interfata. Faza este aleasa astfel incat schimbarea intre
             * sinusuri sa se faca prin trecerea prin Refk0.
             */
            SetCtrlAttribute(panelHandle, PANEL_REFERINTA, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_M_PANTA, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_INALTIME, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_PERIOADA, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_A_SINUS, ATTR_VISIBLE, 1);
            SetCtrlAttribute(panelHandle, PANEL_T_SINUS, ATTR_VISIBLE, 1);

            if (comutare_Sin == 0)
            {
                GetCtrlVal(panelHandle, PANEL_A_SINUS, &A_sin);
                GetCtrlVal(panelHandle, PANEL_T_SINUS, &T_sin);
            }
            else
            {
                if ((Refk_2 < Refk0) && (Refk_1 >= Refk0)) //comutarea de jos in sus
                {
                    comutare_Sin = 0;
                    timp_sinus_tk = 2 * Te;
                }

                if ((Refk_2 > Refk0) && (Refk_1 <= Refk0)) //comutarea de sus in jos
                {
                    comutare_Sin = 0;
                    timp_sinus_tk = 2 * Te + T_sin / 2;
                }
            }
            //formula de calcul pentru SIN 
            local_Refk=A_sin*sin(((2*Pi())/T_sin)*timp_sinus_tk)+Refk0;
	    timp_sinus_tk=timp_sinus_tk+Te;
            break;

        case 3:
            /*
             * Semnal triunghiular.
             *
             * Refk0 este valoarea de la care porneste triunghiul.
             * INALTIME este diferenta dintre valoarea de baza si varf.
             * PERIOADA este durata unui ciclu complet.
             *
             * Folosim direct panta necesara pentru ca triunghiul sa ajunga
             * la Refk0 + INALTIME la jumatatea perioadei si sa revina la
             * Refk0 la sfarsitul perioadei.
             */
            SetCtrlAttribute(panelHandle, PANEL_REFERINTA, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_M_PANTA, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_A_SINUS, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_T_SINUS, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_INALTIME, ATTR_VISIBLE, 1);
            SetCtrlAttribute(panelHandle, PANEL_PERIOADA, ATTR_VISIBLE, 1);

            GetCtrlVal(panelHandle, PANEL_INALTIME, &local_m);
            GetCtrlVal(panelHandle, PANEL_PERIOADA, &local_p);

            if (local_p <= 0)
            {
                /* O perioada invalida nu trebuie sa genereze valori eronate. */
                local_Refk = Refk0;
                timp_triunghi_tk = 0;
                break;
            }

            /*
             * Inceputul unei noi perioade. Se foloseste >= pentru ca faza
             * sa nu depaseasca durata declarata a perioadei.
             */
            if (timp_triunghi_tk >= local_p)
                timp_triunghi_tk = 0;

            if (timp_triunghi_tk < local_p / 2.0)
            {
                /* Urcarea: Refk0 -> Refk0 + INALTIME. */
                local_Refk = Refk0
                           + (2.0 * local_m / local_p) * timp_triunghi_tk;
            }
            else
            {
                /* Coborarea: Refk0 + INALTIME -> Refk0. */
                local_Refk = Refk0
                           + 2.0 * local_m
                           - (2.0 * local_m / local_p) * timp_triunghi_tk;
            }

            timp_triunghi_tk=timp_triunghi_tk+Te;
            break;

        default:
            local_Refk = Refk0;
            break;
    }

    return local_Refk;
}

/* Selecteaza tipul de semnal si initializeaza punctul de pornire. */
int CVICALLBACK selectie_semnal(int panel, int control, int event,
                                void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_COMMIT:
            GetCtrlVal(panelHandle, PANEL_SEL_REF, &sel_ref);

            switch (sel_ref)
            {
                case 0:
                    /* Treapta nu are nevoie de o faza interna. */
                    break;

                case 1:
                    /* Rampa porneste de la valoarea curenta. */
                    timp_rampa_tk = 0;
                    Refk0 = Refk;
                    break;

                case 2:
                    /* Sinusul porneste de la valoarea curenta. */
                    timp_sinus_tk = 0;
                    Refk0 = Refk;
                    break;

                case 3:
                    /* Triunghiul porneste de la valoarea curenta. */
                    timp_triunghi_tk = 0;
                    Refk0 = Refk;
                    break;

                default:
                    break;
            }
            break;
    }

    return 0;
}

/* Reinitializeaza rampa atunci cand utilizatorul modifica panta. */
int CVICALLBACK modificare_Panta(int panel, int control, int event,
                                 void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_COMMIT:
            timp_rampa_tk = 0;
            Refk0 = Refk;
            break;
    }

    return 0;
}

/* Cere schimbarea fazei sinusului la o trecere prin valoarea de baza. */
int CVICALLBACK detectare_comutare_SIN(int panel, int control, int event,
                                       void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_COMMIT:
            comutare_Sin = 1;
            break;
    }

    return 0;
}

/* Reinitializeaza triunghiul atunci cand se modifica perioada sau inaltimea. */
int CVICALLBACK semnal_triunghiular(int panel, int control, int event,
                                    void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_COMMIT:
            timp_triunghi_tk = 0;
            Refk0 = Refk;
            break;
    }

    return 0;
}
