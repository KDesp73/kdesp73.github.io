#include <webc/webc-core.h>
#include <webc/webc-actions.h>

typedef struct { 
    const char* link;
    const char* title;
} Link;

#define MYLINK(t, l) \
    (Link) {.title = t, .link = l}

void links(char** buffer)
{
    Link items[] = {
        MYLINK("My Portfolio", "https://kdesp73.github.io/Portfolio"),
        MYLINK("My Docs", "https://kdesp73.github.io/Docs"),
        MYLINK("webc-site", "https://kdesp73.github.io/webc-site"),
        MYLINK("webc-docs", "https://kdesp73.github.io/webc-docs"),
        MYLINK("iee-api", "https://iee-api-nine.vercel.app/"),
        MYLINK("Watchlist Wizard Website", "https://dmg-techlabs.github.io/Movie-Manager-Website/"),
        MYLINK("What Does My Girlfriend Want To Eat", "https://kdesp73.github.io/What-Does-My-Girlfriend-Want-To-Eat/")
    };

    for(size_t i = 0; i < ARRAY_LEN(items); ++i){
        WEBC_LiStart(buffer, CLASS("link"));
            WEBC_Span(buffer, CLASS("selector"), "> ");
            WEBC_Anchor(buffer, WEBC_UseModifier((Modifier) {.target = "_blank", .href = items[i].link}), items[i].title);
        WEBC_LiEnd(buffer);
    }
}

char* Index()
{
    char* buffer = NULL;
    WEBC_HtmlStart(&buffer, "en");
    WEBC_Head(&buffer, "index.html",
        LINK_STYLESHEET_TAG("./style.css"),
        NULL
    );

    WEBC_BodyStart(&buffer);
        WEBC_H1(&buffer, NO_ATTRIBUTES, "index.html");

        WEBC_Ul(&buffer, CLASS("list"), links);
    WEBC_BodyEnd(&buffer);

    WEBC_HtmlEnd(&buffer);

    return buffer;
}

int main(int argc, char** argv){
    WebcAction action = WEBC_ParseCliArgs(argc, argv);

    Tree tree = WEBC_MakeTree("docs", 
        WEBC_MakeRoute("/", Index()),
        NULL
    );

    WEBC_HandleAction(action, tree);
}
