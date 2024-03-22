

To use `about.cgi` or `blog.cgi` u need to compile this cgi's, this is obviously. But u only compile `index.cgi`.
To fix it I see some solutions:
1. Generate this files, changing all time output filname in project settings of visual studio.
2. Make checks on current url of page and cout only needed tmpl file.
 
I changed your application logic to second variant, cause imho it's better.
To use just use subpath in url that's `index.cgi/your_page/`, where your_page is about, blog and etc.

Working `index.cgi/about/`, `index.cgi/table/`, `index.cgi/blog/`, `index.cgi/index/`



## Tips
- Use delete function. The article to read about this: https://www.geeksforgeeks.org/delete-in-c/
- Move all static cout text to tmpl, if logic of application is still intact.
- Name files(cpp and header) and functions appropriable.  https://www.geeksforgeeks.org/naming-convention-in-c/
- Add comments to your code (is better to use english as comments).
- Add links to just url paths, like i wrote in tmpl files.
