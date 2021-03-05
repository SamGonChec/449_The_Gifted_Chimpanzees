TEMPLATE = subdirs

SUBDIRS += NineMensMorris

CONFIG(debug, debug|release) {
    SUBDIRS += test
}
