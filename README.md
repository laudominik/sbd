# database features
## Project 1 - merge sort on files

### Requirements
- tape implemented as file
- saving pages
- record type: Car registration
- Order type: lexicographic
- algorithm

### Explanation
#### What is a sequential file
Sequential file is a file that consists of records in form of key-value pairs.
The key value pairs should be sorted to allow binary search.
#### How to insert new record?
New record should be inserted to the special area of the file. Then 
to keep the file sorted it should be periodically reorganised.
#### How does the sorting work?
Distribute the file into two tapes (alternate between runs)
Merge files run-wise into single tape.
#### Page size
Block size can be a multiple of record size

