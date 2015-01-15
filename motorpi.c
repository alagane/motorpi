#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <wiringPi.h>

#define PIN1 5
#define PIN2 6
#define PIN3 10
#define PIN4 11

#define N_STEP 8

static int dontstop = 1;

void handler(int s) {
	dontstop = 0;
}

int main(int argc, char *argv[]) {
	// Attente entre chaque pas en microsecondes.
	int pause = 1000; 
	// Compteur de pas.
	int step = 0; 
	// Liste des états des 4 pins pour faire tourner le moteur.
	int matrix[8][4] = {
		{HIGH, LOW, LOW, LOW},
		{HIGH, HIGH, LOW, LOW},
		{LOW, HIGH, LOW, LOW},
		{LOW, HIGH, HIGH, LOW},
		{LOW, LOW, HIGH, LOW},
		{LOW, LOW, HIGH, HIGH},
		{LOW, LOW, LOW, HIGH},
		{HIGH, LOW, LOW, HIGH}
	};

	// Initialisation de wiringPi.
	wiringPiSetup();

	// Initialisation des 4 pins.
	pinMode(PIN1, OUTPUT);
	pinMode(PIN2, OUTPUT);
	pinMode(PIN3, OUTPUT);
	pinMode(PIN4, OUTPUT);

	// Mise des 4 pins à 0.
	digitalWrite(PIN1, LOW);	
	digitalWrite(PIN2, LOW);	
	digitalWrite(PIN3, LOW);	
	digitalWrite(PIN4, LOW);	

	if (argc > 1) {
		signal(SIGALRM, handler);
		alarm(atoi(argv[1]));
	}

	// Boucle principale du programme.
	while (dontstop) {
		// Mise à jour des 4 pins en fonction de la liste.
		digitalWrite(PIN1, matrix[step][0]);
		digitalWrite(PIN2, matrix[step][1]);
		digitalWrite(PIN3, matrix[step][2]);
		digitalWrite(PIN4, matrix[step][3]);
		// Incrémentation du compteur de la liste.
		step = (step + 1) % N_STEP;
		// Pause selon la vitesse du moteur.
		delayMicroseconds(pause);
	}
	
	// Mise des 4 pins à 0.
	digitalWrite(PIN1, LOW);	
	digitalWrite(PIN2, LOW);	
	digitalWrite(PIN3, LOW);	
	digitalWrite(PIN4, LOW);	

	return 0;
}

