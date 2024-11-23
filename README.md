# Multicore Processing

**Introduction**


- [Jacobi Heat Transfer(Open MPI)](#heat-transfer)
- [Filters](filters/README.md)

## Heat Transfer
A conduction Jacobi Heat Transfer simulation on a 2D plate, utilizing parallel processing with the use of MPI,
OpenMP written in C.


**mat.txt is the input file**

The first row is the width and height of the grid
and from the second row, the matrix starts and each index is the temperature at that point
````txt
10 10
100.00	100.00	100.00	100.00	100.00	100.00	100.00	100.00	100.00	100.00	
100.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	100.00	
100.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	100.00	
100.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	100.00	
100.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	100.00	
100.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	100.00	
100.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	100.00	
100.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	100.00	
100.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	100.00	
100.00	100.00	100.00	100.00	100.00	100.00	100.00	100.00	100.00	100.00	
````

**newMat.txt is the output**

````txt
49.98	30.49	22.04	18.71	18.71	22.04	30.49	49.98	
69.45	49.94	38.99	34.09	34.09	38.99	49.94	69.45	
77.87	60.85	49.89	44.60	44.60	49.89	60.85	77.87	
81.19	65.72	55.15	49.86	49.86	55.15	65.72	81.19	
81.19	65.72	55.15	49.86	49.86	55.15	65.72	81.19	
77.87	60.85	49.89	44.60	44.60	49.89	60.85	77.87	
69.45	49.94	38.99	34.09	34.09	38.99	49.94	69.45	
49.98	30.49	22.04	18.71	18.71	22.04	30.49	49.98	
````
