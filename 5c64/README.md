## Studying CLAS12 data cook version 5c.6.4
 various studies related to the data from CLAS12

Magnetic field map study using Run 2391 and Run 2587. Details in the directory 5c64 (Version 5c.6.4 in terms of the cooking of the data)

The Job ID and files are described in [CLAS12 Drift Chamber Alignment Study](https://clasweb.jlab.org/wiki/index.php/CLAS12_Drift_Chamber_Alignment_Study). Download the files by clicking on the Job ID Number Links. For example, the __Job 1__ file is loacted at 
```
/w/hallb-scifs17exp/clas12/bclary/CLAS12/validation/validationBrandon/outfiles/5c.6.4/root_out/out_clas_002391.0.9_job1.root
```
and so on.


### Creating analysis file
Use the macro ```skim.C``` to create files for analysis.

### Study Missing mass distribution
Run the macro ```mmSqfit.c``` to get the analysis done.

### Study Elastic Peak position
Use the macro ```fit.c``` to get the results.

