/*This source code was prepared by:
- Emmanuel Limisi
- Kristian Onjala
- Joshua Ndirangu
- George Williams
- Peter Ngatia
And is under the MIT license */

#include <stdio.h> // used for printf, scanf
#include <stdlib.h> // used for exit, realloc, calloc and free 
#include <string.h>// used for strlen, strcpy

struct Patient{ 
  char *name;
  int id;
  char *medical_history;
};

void add_patient(struct Patient *patient_array[]){
  static unsigned int patient_count = 0;
  char medical_history_buffer[10000];
  char name_buffer[100];
  
  patient_array[patient_count] = calloc(1, sizeof(struct Patient));//allocate memory for new patient
  if (patient_array[patient_count] == NULL) exit(EXIT_FAILURE);// Error handling, checking for failed allocation
  
  printf("Enter patient's name:\n");
  scanf(" %[^\n]",name_buffer);
  patient_array[patient_count]->name = calloc(1, strlen(name_buffer) + 1); //allocate memory for patient's name
  if (patient_array[patient_count]->name == NULL) exit(EXIT_FAILURE);// Error handling by exiting the program if memory allocation failed
  strcpy(patient_array[patient_count]->name, name_buffer);
  
  printf("Enter patient's ID:\n");
  if (scanf("%d", &(patient_array[patient_count]->id)) == 0) exit(EXIT_FAILURE);// Error handling by checking for failed allocation
  
  printf("Enter patient's medical history:\n");
  scanf(" %[^\n]",medical_history_buffer);
  patient_array[patient_count]->medical_history = calloc(1, strlen(medical_history_buffer) + 1); //allocate memory for patient's medical history
  if (patient_array[patient_count]->medical_history == NULL) exit(EXIT_FAILURE);//Program exits if memory allocation fails
  strcpy(patient_array[patient_count]->medical_history, medical_history_buffer);
  printf("\n");
    
  patient_count++;
}

void print_all_records(struct Patient *patient_array[]){
  for(int i = 0; patient_array[i] != NULL; i++){
    printf("Patient %d\n", i + 1);
    if(patient_array[i]->id == 0) printf("Discharged\n");
    else { 
      printf("Name: %s\n", patient_array[i]->name);
      printf("ID: %d\n", patient_array[i]->id);
      printf("Medical History: %s\n", patient_array[i]->medical_history);
    }
    printf("=================================\n");
  }
}

void discharge_patient(struct Patient *patient_array[]){
  int found = 0;
  int patient_id;
  printf("Enter patient's ID\n");
  if (scanf("%d", &patient_id) == 0) exit(EXIT_FAILURE);
  for(int i = 0; patient_array[i] != NULL; i++){
    if (patient_array[i]->id == patient_id){
      found = 1;
      patient_array[i]->id = 0;
      free(patient_array[i]->name);//free memory previously used for patient's name
      free(patient_array[i]->medical_history);//free memory previously used for patient's medical history
      printf("Patient successfully discharged\n");
    }
  }
  if (found == 0) printf("The patient's ID does not exist\n");  
  printf("\n");
}

void update_patient_details(struct Patient *patient_array[]){
  int patient_id;
  int found = 0;
  char medical_history_buffer[10000];
  printf("Enter patient's ID\n");
  if (scanf("%d", &patient_id) == 0) exit(EXIT_FAILURE);
  for(int i = 0; patient_array[i] != NULL; i++){
    if (patient_array[i]->id == patient_id){
      found = 1;
      printf("Enter new medical history\n");
      scanf(" %[^\n]",medical_history_buffer);
      patient_array[i]->medical_history = realloc(patient_array[i]->medical_history, strlen(medical_history_buffer) + 1);//reallocate memory for new size of patient's medical history
      if (patient_array[i]->medical_history == NULL) exit(EXIT_FAILURE);//program exits if realloc fails
      strcpy(patient_array[i]->medical_history, medical_history_buffer);
      printf("Medical history successfully updated\n");
    }
  }
  if (found == 0) printf("The patient's ID does not exist\n");
  printf("\n");
}

void free_patient_array_data(struct Patient *patient_array[]){
  for(int i = 0; patient_array[i] != NULL && patient_array[i]->id != 0; i++){ // The && is used to prevent a double free when the patient is discharged
    free(patient_array[i]->name);
    free(patient_array[i]->medical_history);
  }
}

int main(void){
  int answer;
  struct Patient **patient_array = calloc(100, sizeof(struct Patient *));//calloc is used to ensure zero initialization
  printf("Welcome to the Health Management System\n");
  printf("Created by EL - 0698, KO - 0704, JN - 1268, GW - 0744, PN - 0729\n");
  while(answer != 5){ 
    printf("What do you want to do ?\n");
    printf("(1) View all patient's records\t (2) Add a patient\n");
    printf("(3) Update a patient's history\t (4) Discharge a patient\n");
    printf("(5) Exit\n");
    if (scanf("%d", &answer) == 0) answer = 5;
    printf("\n");
    switch (answer){
      case 1: print_all_records(patient_array); break;
      case 2: add_patient(patient_array); break;
      case 3: update_patient_details(patient_array); break;
      case 4: discharge_patient(patient_array); break;
      case 5: answer = 5; break;
    }
  }
  free_patient_array_data(patient_array);//clean up to ensure there is no memory leak when the program exits successfully
  free(patient_array);//clean up to ensure there is no memory leak when the program exits successfully
  return 0;
}
