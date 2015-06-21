# Documentation
This is a really rough document for the LLM language. Note that this language
is mostly a fun side project more than anything serious...

LLM uses fastcgi to communicate with your web server, this means it's really
easy to setup and integrate with existing servers like Apache and Nginx, and
it's reasonably fast.

## Markup
LLM can be used for markup in replace of HTML. The section below describes how
you would use it as markup, and also the preferred styling for particular syntax.
It is recommended that you use 2 spaces in a tab instead of the typical 4 or 8. LLM
documents should be saved with the extension `llm`.

### Elements
Elements in LLM are defined with parenthesis, for example a break or `br`, would
be defined as follows:

    (br)

Elements that have content in them are defined like so:

    (p "some text")

Note that text must be surrounded with quotations, you can have as many string literals
in an element as you like:

    (p 
      "some text"
      " more text!!!" "and more!"
    )

You can also have elements inside of elements:

    (div
      (h1 "this is my divisions heading")
      (p
        "and some content!"
      )
    )

### Attributes

Attributes are denoted with square brackets, `[]`.
For instance, you would write the following to set the 
class attribute for a div to "classname".

    (div [class "classname"]
      (h1 "woo")
    )

You can have multiple attributes:

    (div [class "classname"] [id "idname"]

    )

However, if there are multiple attributes, it is suggested you format them like this if it has more than one child:

    (div 
      [class "classname"] 
      [id "idname"]
      (p "woo")
      (p "another child")
      (p "yeyeye")
    )

