# QUESTION 1
You are tasked with building a dynamic patient records system for a hospital using C. The system must:
- Add new patients (allocate memory for patient details: name, ID, medical history).
- Update records (expand/shrink memory if medical history updates).
- Remove discharged patients (free memory).
- Handle errors (e.g., failed allocations, NULL checks).

## Our approach
- We defined patient as a struct having 3 fields, `id`, `name` & `medical_history`.
- We split the key functional requirements into seperate functions.
- We decided to store all the patients in memory as a zero-initialized array (done via `calloc()`).
- Each function takes in the array as the arguement.

### add_patient
- `patient_count` keeps track of how many patients have been added.
- It is static so that it is incremented each time the function is called.
- Whenever the function is called, space is allocated on the patient's array
- The user enters the patient's name which is stored in a buffer.
- Space is allocated for the name field in the struct and the name is copied over.
- Same to medical history.

### print_all_records
- It loops through the whole array checking for the first NULL element to stop at.
- Before reaching there, it displays the details of each patient.
- If a patient's `id` is 0, it means they were discharged.

### discharge_patient
- It also loops through all allocated elements of the array.
- It checks for a match in the inputted id, if it matches: 
  - `id` is set to 0 
  - Space allocated for name and medical history are both freed.
- `id` is set to 0 instead of freeing so as to avoid gaps as the array ought to be contiguous for the loop to be effective.

### update_patient_details
- Also loops through the array of patients
- If it finds a match:
  - The new history is saved to a buffer
  - `realloc()` is then called to resize the `medical_history` field with the new length.
  - The new `medical_history` is then copied over.

### free_patient_array
- This is the clean up function, called when the program is exiting
- It loops through the patient array so as to free the memory allocated to `name` and `medical_history`
- It first checks whether the `id == 0` so as to avoid a double free.

### main
- The entry point
- This is where the array of patients is zero initialized by `calloc()`.
- The purpose of this is to avoid garbage elements and to be able to loop through it contiguosly so long as an element is non-NULL.
- The program runs in a loop giving the user choices based on what they wish to do.
- Depending on the user's choice, the corresponding appropriate function is called.
- When the loop exits, `free_patient_array()` is called and memory allocated by `calloc()`.

## What I learnt
- One can use `%[^\n]` as a format specifier so as to capture a sentence containing spaces till a new line is reached.
- One ought to put a ` ` like so ` %[^\n]` if you have multiple `scanf()` calls because the `\n` isn't consumed, so on subsequent calls, `scanf()` either returns abruptly or consumes wrong input.

## What I loved
- I found declaring `patient_count` as static to be very fitting for this use case and greatly simplified the program design.
- The use of a switch statement and how each case is a one-liner, looks fitting.

## Improvements noted
- I should have used `break` after a match was found so as to avoid unnecessary iterations.
- The lookup process should have probably been in its seperate function as it has been used twice.

## Perfomance concern
- The use of an array as the data store makes this program O(n) which is okay as n is small, but at a larger scale a different approach should be considered.

# Question 2
Design a C-based system to manage traffic light data for a smart city. The system must:
- Dynamically allocate/deallocate memory for traffic sensors.
- Handle buffer overflows (e.g., corrupt sensor data).
- Prevent memory leaks (e.g., faulty sensor removal).
- Simulate garbage collection for orphaned data.

## Our approach
- Pretty much the same as the patient record system save for:
  - The inclusion of a basic, manual garbage collector.
  - The absence of an update function
  - More care being taken for checking buffer overflows.

# Conclusion
- Fun project it was.
- Shoutout to my group members for their commitment and dedication:
  - We did the whole assignment fully & purely online, with no physical meetups.
