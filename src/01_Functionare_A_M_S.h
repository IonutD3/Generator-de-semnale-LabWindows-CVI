/*
 * Gestioneaza modul de functionare Automat sau Manual si starea LED-ului.
 */
int functiune_Automat_Manual(void)
{
    GetCtrlVal(panelHandle, PANEL_BINARYSWITCH, &regim);

    if (regim)
    {
        /* In modul Manual, utilizatorul controleaza direct LED-ul. */
        SetCtrlAttribute(panelHandle, PANEL_BINARYSWITCH_2, ATTR_DIMMED, 0);
        GetCtrlVal(panelHandle, PANEL_BINARYSWITCH_2, &stare_led);
        SetCtrlVal(panelHandle, PANEL_LED, stare_led);
    }
    else
    {
        /* In modul Automat, LED-ul este comutat la fiecare esantionare. */
        SetCtrlAttribute(panelHandle, PANEL_BINARYSWITCH_2, ATTR_DIMMED, 1);
        GetCtrlVal(panelHandle, PANEL_LED, &valoare_led);

        if (valoare_led == 0)
            SetCtrlVal(panelHandle, PANEL_LED, 1);
        else
            SetCtrlVal(panelHandle, PANEL_LED, 0);
    }

    return 0;
}
