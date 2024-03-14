#include "MyShell.h"
#include "MyFunctionShell.h"
int main()
{
    char str[] = "cd OneDrive - Ariel University";
    char** arguments = splitArguments(str);
     for (int i = 0; arguments[i] != NULL; i++) {
        printf("%s\n", arguments[i]);
    }
    free(arguments);

    wellcome();
    while (1)
    {
        getLocation();
        char *str = inputFromUser();
        if (strcmp(str, "exit") == 0)
            logout(str);
        char **arguments = splitString(str);

        if (strcmp(str, "echo") == 0)
            echo(arguments);
        if (strcmp(str, "cd") == 0)
            cd(arguments);
        if (strcmp(str, "cp") == 0)
            cp(arguments);

        free(str);
        free(arguments);
    }

    return 0;
}






//                     aSPY//YASa
//              apyyyyCY//////////YCa       |
//             sY//////YSpcs  scpCY//Pp     | Welcome to myShell
//  ayp ayyyyyyySCP//Pp           syY//C    | Version 2.4.3
//  AYAsAYYYYYYYY///Ps              cY//S   |
//          pCCCCY//p          cSSps y//Y   | https://github.com/<user>
//          SPPPP///a          pP///AC//Y   |
//               A//A            cyP////C   | Have fun!
//               p///Ac            sC///a   |
//               P////YCpc           A//A   | Craft packets like it is your last
//        scccccp///pSP///p          p//Y   | day on earth.
//       sY/////////y  caa           S//P   |                      -- Lao-Tze
//        cayCyayP//Ya              pY/Ya   |
//         sY/PsY////YCc          aC//Yp
//          sc  sccaCY//PCypaapyCP//YSs
//                   spCPY//////YPSps
//                        ccaacs
//                                        using c                                    using c

void welcome()
{
    printf("   G   G  RRRRR  EEEEE  ETTTTT IIIIII N   N  GGGGG  SSSSS\n");
    printf("  G G G  R    R  E        T     I   N   N G     G S     S\n");
    printf(" G     G RRRRR   EEEE     T     I   N   N G       SSSSS\n");
    printf(" G     G R   R   E        T     I   N   N G     G       S\n");
    printf("  G G G  R    R  EEEE     T   IIIIII NNNNN  GGGGG  SSSSS\n");

    printf("Greetings from MyShell\n");
    printf("https://github.com/<username>\n");
}
