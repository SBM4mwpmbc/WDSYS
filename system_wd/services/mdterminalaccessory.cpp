#include "mdterminalaccessory.h"
#include <string>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include <array>
#include <iostream>
#include <stdio.h>
#include <filesystem>

// goes in order
bool acc1 = "mdterminalcmdhelp.fardx";
bool acc2 = "mdterminalarrayacc.fardx";
bool acc3 = "mdterminaluserauthdata.fardx";
bool acc4 = "mdterminalnamehelp.fardx";
bool acc5 = "mdterminalaccextra.fardx";

bool acclist()
{
    printf("Accessories available for mdterminal: \n");
    printf("Accessory 1: ", acc1, "\n");
    printf("Accessory 2: ", acc2, "\n");
    printf("Accessory 3: ", acc3, "\n");
    printf("Accessory 4: ", acc4, "\n");
    printf("Accessory 5: ", acc5, "\n");
    return 0;
}


int main(void)
{
    printf("mdterminal startup detected, listing accessories..\n");

    if (acclist() != 0)
    {
        printf("Error listing accessories, exiting..\n");
        return 1;
    }
    else
    {
        printf("Accessories listed successfully, exiting..\n");
        return 0;
    }
}