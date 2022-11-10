# senior_project
COMP 495 Senior Project - Text Highlighter



/****************** Brain Storming!! **********************
* Must Haves:
    - Identify User-Definable Text and Highlight it
    - Identify User-Definable Text in a language different than document
    - Independent of character case
    - Should be able to find Names and highlight ("textual units")

* Process Described:
    - Step 1: Receive Text
    - Step 2: Identifying each token in the text
    - Step 3: Select a token
    - Step 4: Determine if token includes user-definable prefix, root,
                suffix, textual unit, and also token's length
    - Step 5: Replace each identified prefix, root, suffix, with a 
                standard form of the same.
    - 