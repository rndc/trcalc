/**
 * trcalc.c
 *
 * trcalc - throughput rate calculator
 *
 * Version 1.0 (2012-10-15)
 * Copyleft (c) 2012 Agus Bimantoro
 *
 * This tool is table conversion for throughput speed,
 * and calculation of estimate time to transfer file.
 * ***********************************************************************
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */


#include <stdio.h>
#include <stdlib.h>

void helps(void)
{
    printf("trcalc 1.0 - throughput rate calculator\n\n");
    printf("Usage: trcalc <options> [VALUE]\n");
    printf("Options: \n");
    printf("\t-b  bits\n");
    printf("\t-k  kilobits\n");
    printf("\t-m  megabits\n");
    printf("\t-g  gigabits\n");
    printf("\t-B  bytes\n");
    printf("\t-K  kilobytes\n");
    printf("\t-M  megabytes\n");
    printf("\t-G  gigabytes\n");
    printf("\t-S  estimate time to transfer a file, needs [speed/kbps] and [size of file /KB/MB/GB]\n");
    printf("\t    see example below for usage.\n\n");
    printf("Example: trcalc -K 125\n");
    printf("         trcalc -m 1\n");
    printf("         trcalc -S 1000 -K 1024\n\n");
    printf("Please report bugs to <l0g.bima@gmail.com>\n");
    exit(0);
}

int main(int argc, char *argv[])
{
    char unit[100];
    double value, speed, ftime, bit, kbit, mbit, gbit, byte, kbyte, mbyte, gbyte;
    int hourmod, hour, minute, second;

    // if argument less than 3 goto help then exit
    if (argc < 3)
    {
        helps();
    }

    if ((int) argv[1][0] == '-')
    {
        value = atof(argv[2]);
        switch ((int) argv[1][1])
        {
            case 'b':
                bit = value;
                kbit = bit / 1000;
                mbit = kbit / 1000;
                gbit = mbit / 1000;
                byte = (kbit / 8) * 1024;
                kbyte = kbit / 8;
                mbyte = kbyte / 1024;
                gbyte = mbyte / 1024;
                break;

            case 'k':
                kbit = value;
                bit = kbit * 1000;
                mbit = kbit / 1000;
                gbit = mbit / 1000;
                byte = bit / 8;
                kbyte = kbit / 8;
                mbyte = kbyte / 1024;
                gbyte = mbyte / 1024;
                break;

            case 'm':
                mbit = value;
                bit = mbit * 1000000;
                kbit = mbit * 1000;
                gbit = mbit / 1000;
                byte = bit / 8;
                kbyte = kbit / 8;
                mbyte = kbyte / 1024;
                gbyte = mbyte / 1024;
                break;

            case 'g':
                gbit = value;
                bit = gbit * 1000000000;
                mbit = gbit * 1000;
                kbit = mbit * 1000;
                gbyte = gbit / 8;
                mbyte = gbit * 1024;
                kbyte = mbyte * 1024;
                byte = kbyte * 1024;
                break;

            case 'B':
                byte = value;
                bit = byte * 8;
                kbit = bit / 1000;
                mbit = bit / 1000000;
                gbit = mbit / 1000;
                kbyte = byte / 1024;
                mbyte = kbyte / 1024;
                gbyte = mbyte / 1024;
                break;

            case 'K':
                kbyte = value;
                byte = kbyte * 1024;
                kbit = kbyte * 8;
                bit = kbyte * 1000;
                //mbit = bit/1000000;
                mbit = kbit / 1000;
                gbit = mbit / 1000;
                mbyte = kbyte / 1024;
                gbyte = mbyte / 1024;
                break;

            case 'M':
                mbyte = value;
                byte = mbyte * 1048576;
                mbit = mbyte * 8;
                bit = mbit * 1000000;
                kbit = bit / 1000;
                gbit = mbit / 1000;
                kbyte = mbyte * 1024;
                gbyte = mbyte / 1024;
                break;

            case 'G':
                gbyte = value;
                byte = gbyte * 1073741824;
                gbit = gbyte * 8;
                mbit = gbit / 1000;
                kbit = mbit / 1000;
                bit = kbit / 1000;
                kbyte = gbyte * 1048576;
                mbyte = gbyte * 1024;
                break;

            case 'S':
                if (argc < 5)
                {
                    helps();
                };
                speed = atof(argv[2]);
                if ((int) argv[3][0] == '-')
                {
                    value = atof(argv[4]);
                    switch ((int) argv[3][1])
                    {
                        case 'K':
                            strcpy(unit, " KiloBytes");
                            strcat(argv[4], unit);
                            ftime = (((1 * value) * 1024) * 8) / (speed * 1000);
                            break;

                        case 'M':
                            strcpy(unit, " MegaBytes");
                            strcat(argv[4], unit);
                            ftime = (((1024 * value) * 1024) * 8) / (speed * 1000);
                            break;

                        case 'G':
                            strcpy(unit, " GigaBytes");
                            strcat(argv[4], unit);
                            ftime = (((1048576 * value) * 1024) * 8) / (speed * 1000);
                            break;

                        default: helps();
                    }

                    hourmod = (int) ftime % 3600;
                    hour = (int) ftime / 3600;
                    minute = hourmod / 60;
                    second = (int) ftime % 60;

                    printf("\nSpeed of connection: %s kbps\n", argv[2]);
                    printf("Size of file: %s\n", argv[4]);
                    printf("Estimated time: %i:%i:%i\n\n", hour, minute, second);
                    exit(0);
                }
                else
                {
                    helps();
                }
                break;

            default: helps();
        }

        printf("\nbits: %g\nkilobits: %g\nmegabits: %g\ngigabits: %g\n\nBytes: %g\nKiloBytes: %g\nMegaBytes: %g\nGigaBytes: %g\n\n", bit, kbit, mbit, gbit, byte, kbyte, mbyte, gbyte);
    }
    else
    {
        helps();
    }

    return 0;
}
