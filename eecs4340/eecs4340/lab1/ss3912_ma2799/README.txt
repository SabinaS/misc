EECS4340- Lab 1- Content-Addressable Memory (CAM)

Authors: Mark Aligbe (ma2799), Sabina Smajlaj (ss3912)

----Functionality----

A CAM is just a special type of memory array, so just like for any 
memory element, we wanted a component that allows us to store information.
For this, we used 32 enable registers, one for each of the 32 entries.
eff.sv contains the register specification, and our CAM is specified in
cam.sv.

To write and read from specific indeces, we relied on Verilog's ability 
to handle indeces and hence did not need a decoder. 

The structural representation of our search is as follows: we computed the
equality of the search data with the values in the registers. Then, we ANDed
the result of this comparison with the valid bit of the registers,
generating 32 truth values (the data in the register is the same as what
is being searched and is valid data) which were directly wired to the
priority encoder. The priority encoder, priority_encoder.sv, is purely
combinational, and the truth generator, search_comb.sv, is purely
structural (does not contain behavioral or combinational logic, it strictly
defines the above comparator and AND design). 

The write, read, and search functions in our CAM are purely combinational,
and designed to allow users to continually be able to do any function and
also be able to do any of them in parallel. As a general note, resets in the
CAM are asynchronous, but for the registers, resets are synchronous.

---Documentation---
The lab specification was used to complete the assignment. The only sources
used in the final design are our experience (for example, the Stanford
Encoder template was not used, and we decided to favor more structural than
behavioral code). Two auxillary files were used; GeneratePE.java and
GenerateTest.java. GeneratePE created the case statements used in our
priority encoder, so as to avoid any human errors. GenerateTest was used ot
generate our entire CAM test suite, to test all cases in a variety of
scenarios.

In our testing, we noted that if we raise a signal, we have to wait for that
signal to propagate. To be precise, asserting a search at the same time that
search is issued causes the assertion to fail, while waiting
(asynchronously) allows the assertion to pass.

