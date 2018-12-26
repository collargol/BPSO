Application can be run with parameters to specify paths and objective function:
- 0 parameters: 0 objfcn as objective function
		"gender_data.csv" as input 
		"solution.csv" as output
- 1 parameter:  argv[0] as objective function (0 OR 1)
		"gender_data.csv" as input 
		"solution.csv" as output
- 2 parameters: argv[0] as objective function (0 OR 1)
		argv[1] as input
		"solution.csv" as output
- 3 parameters: argv[0] as objective function (0 OR 1)
		argv[1] as input
		argv[2] as output

objective functions:
0 : based on standard deviations and mean values
1 : based on mean values