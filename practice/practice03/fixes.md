Documented Bugs and Fixes:

Line 9 of practice03.cpp: sumRange function
	Bug: sum not as expected. For loop did not include end number.
	Fix: added an = to the i < end to be i <= end.
Test Passed.

Line 16 of practice03.cpp: containsNegative function
	Bug: loop goes out of scope. Causes undefined behavior due to using [] for indexing.
	Fix: removed the = from the i <= numbers.size() to be i < numbers.size().

Line 17 of practice03.cpp: containsNegative function
	Bug: returned true for positive numbers rather than negative numbers.
	Fix: changed the > to a < to test if the numbers were less than 0 instead of greater than.
Test Passed
