/*This source code was prepared by:
- George Williams
- Emmanuel Limisi
- Kristian Onjala
- Joshua Ndirangu
- Peter Ngatia
And is under the MIT license*/

#include <stdio.h> // printf, scanf
#include <stdlib.h> // exit, malloc, calloc, free
#include <string.h> // strlen, strcpy

#define MAX_DATA_LENGTH 256
#define LAST_ELEMENT 99

typedef struct {
    unsigned int id;
    int colour;
    char location[MAX_DATA_LENGTH];
    int is_functional;
} TrafficSensor;

void addSensor(TrafficSensor *traffic_sensors[]){
    static unsigned int current_sensor = 0;
    char location_buffer[MAX_DATA_LENGTH + MAX_DATA_LENGTH];
    traffic_sensors[current_sensor] = calloc(1, sizeof(TrafficSensor));//allocate memory for new sensor
    if (traffic_sensors[current_sensor] == NULL) exit(EXIT_FAILURE);
    
    traffic_sensors[current_sensor]->id = current_sensor; // auto-assign id to sensor

    
    printf("Enter current traffic light colour:\n");
    printf("(0)RED, (1)AMBER, (2)GREEN\n");
    if (scanf("%d", &(traffic_sensors[current_sensor]->colour)) == 0) exit(EXIT_FAILURE);
    if (traffic_sensors[current_sensor]->colour > 2 || traffic_sensors[current_sensor]->colour < 0) { 
        printf("Traffic light colour invalid\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Enter location:\n");
    scanf(" %[^\n]", location_buffer);
    if (strlen(location_buffer) >= MAX_DATA_LENGTH) exit(EXIT_FAILURE); // check for buffer overflow and exit if happens
    strcpy(traffic_sensors[current_sensor]->location, location_buffer);

    printf("Is the sensor functional:\n");
    printf("(1)Yes (2)No\n");
    if (scanf("%d", &(traffic_sensors[current_sensor]->is_functional)) == 0) exit(EXIT_FAILURE);
    if (traffic_sensors[current_sensor]->is_functional < 1 || traffic_sensors[current_sensor]->is_functional > 2){
        printf("invalid answer\n");
        exit(EXIT_FAILURE);
    }

    printf("\n");
    
    current_sensor++;
}

void removeSensor(TrafficSensor *traffic_sensors[]){
    int found = 0;
    int sensor_id;
    printf("Enter sensor's id:\n");
    if (scanf("%d", &sensor_id) == 0) exit(EXIT_FAILURE);
    for(int i = 0; traffic_sensors[i] != NULL; i++){
        if (traffic_sensors[i] != traffic_sensors[LAST_ELEMENT] && traffic_sensors[i]->id == sensor_id){
            found = 1;
            free(traffic_sensors[i]);// memory deallocated if a sensor is removed from the system
            traffic_sensors[i] = traffic_sensors[LAST_ELEMENT];
            printf("Sensor removed successfully\n");
        }
    }
    if (found == 0) printf("The sensor ID does not exist\n");  
    printf("\n");
}

void garbageCollection(TrafficSensor *traffic_sensors[]) { 
    for (int i = 0; traffic_sensors[i] != NULL; i++){
        if (traffic_sensors[i] != traffic_sensors[LAST_ELEMENT] && traffic_sensors[i]->is_functional == 2) { // check if sensor is faulty and free memory allocated to it if so
            free(traffic_sensors[i]);
            traffic_sensors[i] = traffic_sensors[LAST_ELEMENT]; // assign dangling pointer to point to last element in array
        }
    }
    printf("Freed all the orphaned data!\n");
}

void printSystemStatus(TrafficSensor *traffic_sensors[]) {
    for (int i = 0; traffic_sensors[i] != NULL; i++){
        if (traffic_sensors[i] != traffic_sensors[LAST_ELEMENT]) {
            printf("Sensor ID: %d\n",traffic_sensors[i]->id);
            printf("Traffic color: %s\n",traffic_sensors[i]->colour == 0 ? "RED" : traffic_sensors[i]->colour == 1 ? "AMBER" : "GREEN");
            printf("Location: %s\n",traffic_sensors[i]->location);
            printf("Status: %s\n",traffic_sensors[i]->is_functional == 1 ? "FUNCTIONAL" : "FAULTY");
            printf("======================================================\n");
        }
    }
}

void cleanupSystem(TrafficSensor *traffic_sensors[]){
    for (int i = 0; traffic_sensors[i] != NULL; i++)
        if (traffic_sensors[i] != traffic_sensors[LAST_ELEMENT]) free(traffic_sensors[i]);
}

int main(void) {
    TrafficSensor **traffic_sensors = calloc(100, sizeof(TrafficSensor *));
    if (traffic_sensors == NULL) exit(EXIT_FAILURE);
    traffic_sensors[LAST_ELEMENT] = malloc(sizeof(TrafficSensor));
    printf("Welcome to the TRAFFIC LIGHT MANAGEMENT SYSTEM\n");
    printf("Created by GW - 0744, KO - 0704, JN - 1268, EL - 0698, PN - 0729\n");
    int answer;
    while(answer != 5){ 
        printf("What do you want to do ?\n");
        printf("(1) Add a sensor\n(2) View system state\n");
        printf("(3) Perform Garbage collection\n(4) Remove a sensor\n(5) Exit the system\n");
        if (scanf("%d", &answer) == 0) answer = 4;
        printf("\n");
        switch (answer){
            case 1: addSensor(traffic_sensors); break;
            case 2: printSystemStatus(traffic_sensors); break;
            case 3: garbageCollection(traffic_sensors); break;
            case 4: removeSensor(traffic_sensors); break;
            case 5: answer = 5; break;
        }
    }
    /*The functions ensure all the memory allocated is freed when the program exits, hence prevents memory leaks*/
    cleanupSystem(traffic_sensors);
    free(traffic_sensors[LAST_ELEMENT]);
    free(traffic_sensors);
    return 0;
}
