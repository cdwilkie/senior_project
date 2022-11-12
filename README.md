# senior_project
COMP 495 Senior Project - Text Highlighter



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