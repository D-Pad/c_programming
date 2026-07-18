# Paycheck Calculator
A simple paycheck calculator in C. Compile with the **build.sh** script. Pass 
`-t` into the build.sh script to run a series of tests.

### OPTIONS
 - **r RATE:** Set hourly pay rate (required)
 - **h HOURS:** Set regular hours worked (max 40 before OT)
 - **d HOURS:** Set double time hours (paid at 2x rate)
 - **t RATE:** Set tax rate as decimal (e.g. 0.22 for 22%%)
 - **j:** Data is output in json format

### EXAMPLES
```bash 
paycheck -r 25.50 -h 45 -t 0.18
paycheck -r 30 -h 38 -d 3 -t 0.25
paycheck -r 15 -h 60 -t 0.12 -j
```

### NOTES
 - Hours above 40 are automatically treated as overtime (1.5x)
 - Use -d for double time hours
 - All values are passed by value to the internal functions
 - Run with no arguments to see this help



