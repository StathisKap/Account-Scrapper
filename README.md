# Account-Scrapper

Find results from only one custom search engine.
My custom engine look in Instagram
##Input:
You'll need to create a file named secrets.h  in the inlcude folder, with this format

        char Custom_Search_Engine_Key[] = "&key=[YOUR-KEY]";
        char Custom_Search_Engine_cx[] = "cx=16be1f5c9a14bd768";

Feel free to use my cx, but you'll need your own key. (which you can get from [here](https://developers.google.com/custom-search/v1/overview "here"))
The querry is passed as an argument. ex ./bin/searches "Museums"

## Output: 
Json file, in a folder that will be created called "Searches"

## Stack:
<ul>
    <li>gcc
    <li>libcurl
    <li>make 
</ul>
to build you just run make
