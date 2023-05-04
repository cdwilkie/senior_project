# senior_project
COMP 495 Senior Project - Text Highlighter
Welcome!

This program searches for user-defined textual units contained within a text source.
The program accepts command-line input for a file path, otherwise will prompt user
for path to text source to parse.

Program also parses contents of data/prefix.txt, data/suffix.txt, data/root.txt, and data/dq.txt to
generate an unordered_map. Each line of the afforementioned text files must adhere
to a specific format: "Key" "Value", where "Key" is any unicode string enclosed in quotes,
and "Value" is any unicode string enclosed in quotes. The key and value are separated by
whitespace.

Prefix, Suffix, Root, and DQ text files should contain the search parameter "Key"
and, if desired, a standard form or transliteration for the key, "Value". Should no
standard form or transliteration exist, "null" should be used. Each line must have
a "key" "value" pair. Example Key=Joe Value=Joseph -> "Joe" "Joseph"

Output is written to data/outfile.html, where matching tokens have been written
in bold and non-matching tokens are written in the standard text


/****************** Brain Storming!! **********************
* Must Haves:
    - Identify User-Definable Text and Highlight it
    - Identify User-Definable Text in a language different than document
    - Independent of character case
    - Should be able to find Names and highlight ("textual units")

    - Data Structures:
        - Array - Store and index each token as they appear in source file
        - Unordered Map<string OR int, list>
            - Would map the token type (identified with a string or int) to the indeces 
              in Array that contain that token.

    - Text Output
        - Basic. May not preserve formatting for simplicity.

* Process Described:
    - Step 1: Receive Text
    - Step 2: Identifying each token in the text
    - Step 3: Select a token
    - Step 4: Determine if token includes user-definable prefix, root,
                suffix, textual unit, and also token's length
    - Step 5: Replace each identified prefix, root, suffix, with a 
                standard form of the same.
    - Step 6: If there is an unselected token, select the token next
                in sequence and return to Step 4.
    - Step 7: Reselect the token selected in the third step.
    - Step 8: If reselected token does not start a user-definable textual
                unit, then print the reselected token in a first font,
                reselecting the token next in sequence and repeating
                Step 8. If no token, stop.
    - Step 9: If reselected toekn does start a user-definable textual unit,
                then the ninth step of the method is marking the reselected
                token for highlighting, reselecting the token next in
                sequence, and if no tken to reselect, then printing in the 
                second font the reselected token marked for highlighting and stopping.
    - Step 10: 