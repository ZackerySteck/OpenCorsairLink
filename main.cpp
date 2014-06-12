#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "CorsairLinkProto.h"
#include "CorsairLink.h"
#include "CorsairFan.h"
#include "CorsairLed.h"
#include "CorsairTemp.h"
#include "options.h"

CorsairLink *cl = new CorsairLink();
CorsairFan *f = new CorsairFan();
CorsairLed *l = new CorsairLed();
CorsairTemp *t = new CorsairTemp();

int main(int argc, char **argv) {
	fprintf(stdout, "Open Corsair Link\n");
	int fanNumber = 0, fanMode = 0, fanRPM = 0;
	int ledNumber = 0, ledMode = -1;
	if(parseArguments(argc, argv, fanNumber, fanMode, fanRPM, ledNumber, ledMode, l->color))
	{
		return 1;
	}

	if(!cl->Initialize()) {
		fprintf(stdout, "Cannot initialize link.\n");
		delete cl;
		return 1;
	}

	if(fanNumber != 0) {
		if(fanMode != 0 || fanRPM != 0) {
			if(fanMode == FixedRPM && fanRPM <= 0) {
				fprintf(stderr, "Fan RMP missing for Fixed RPM fan mode.\n");
				return 1;
			}
			else {
				CorsairFan::CorsairFanInfo newFanInfo;
				//fan->SelectFan(fanNumber - 1);
				if(fanMode != 0) {
					fprintf(stdout, "Setting fan to mode %s\n", CorsairFan::GetFanModeString(fanMode));
					newFanInfo.Mode = fanMode;
				}
				if(fanRPM != 0) {
					fprintf(stdout, "Setting fan RPM to %i\n", fanRPM);
					newFanInfo.RPM = fanRPM;
				}
				f->SetFansInfo(fanNumber - 1, newFanInfo);
			}
		} else {
			fprintf(stdout, "No mode or fan RPM specified for the fan.\n");
			return 1;
		}
	}
	else if(ledNumber != 0) {
		l->SelectLed(ledNumber - 1);
		fprintf(stdout, "Setting LED\n");
		if (ledMode > -1) {
			l->SetMode(ledMode);
		}
		int current_mode = l->GetMode();
		//fprintf(stdout, "DEBUG Current LED Mode: %02x\n", current_mode);
		if ((current_mode == 0x0C) && (l->color_set_by_opts == 3)) {
			l->Set_TempMode_Color(l->color);
		}
		if ((current_mode != 0x0C)&&(l->color_set_by_opts > 0)) {
			//fprintf(stdout, "DEBUG Setting Led Colorset; colors defined: %i\n", l->color_set_by_opts);
			l->SetLedCycleColors(l->color);
		}
	}
	else if(fanMode != 0 || fanRPM != 0) {
			fprintf(stderr, "Cannot set fan to a specific mode or fixed RPM without specifying the fan number\n");
			return 1;
	}
	else {
		int i = 0;

		fprintf(stdout, "Number of Controllable LEDs: %i\n", l->GetLedCount());
		fprintf(stdout, "LED Mode: %02X\n", l->GetMode());
		l->GetColor(&l->color[0]);
		fprintf(stdout, "LED Color:\n\tRed: %i\n\tGreen: %i\n\tBlue: %i\n", l->color[0].red, l->color[0].green, l->color[0].blue );
		fprintf(stdout, "Number of Temperature Sensors: %i\n", t->GetTempSensors());
		fprintf(stdout, "Temperature: %.2f C\n", t->GetTemp(0)/256);

		for(i = 0 ; i< 5; i++) {
			f->ReadFanInfo(i, &f->fanInfo[i]);
			f->PrintInfo(f->fanInfo[i]);
		}
	}

	if(cl != NULL) {
		delete cl;
	}
	return 0;
} 
