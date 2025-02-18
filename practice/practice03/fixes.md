Documented Bugs and Fixes:

sumRange function:
	Bug: sum not as expected. For loop did not include end number.
	Fix: added an = to the i < end to be i <= end.
	Test Passed.

containsNegative function:
	Bug: loop goes out of scope. Causes undefined behavior due to using [] for indexing.
	Fix: removed the = from the i <= numbers.size() to be i < numbers.size().
	Test Passed

	Bug: returned true for positive numbers rather than negative numbers.
	Fix: changed the > to a < to test if the numbers were less than 0 instead of greater than.
	Test Passed

	Bug: when given an empty vector, it would simply return as false, with no other information.
	Fix: added logic to throw an error to user letting them know the vector was empty then returned as false.
	Test Passed