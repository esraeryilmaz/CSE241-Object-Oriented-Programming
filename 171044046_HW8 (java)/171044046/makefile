JFLAGS = -g
JC = javac
.SUFFIXES: .java .class

.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
    GTUContainer.java \
    GTUSet.java \
    GTUVector.java \
    Main.java

default: classes

run: classes
	java Main

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class