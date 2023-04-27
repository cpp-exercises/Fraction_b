<div dir="rtl" lang="en">

# Fraction
Write a class named Fraction that represents a fraction of two integers. Overload the following operators for this class:

* The + operator to add two fractions and return their sum as another fraction in reduced form.
* The - operator to subtract two fractions and return their difference as another fraction in reduced form.
* The * operator to multiply two fractions and return their product as another fraction in reduced form.
* The / operator to divide two fractions and return their quotient as another fraction in reduced form.
* The == operator to compare two fractions for equality and return true or false.
* All comparison operations (>,<,>=,<=)
* The ++ and -- operator that adds (or substracts) 1 to the fraction. implement both pre and post fix.
* The << operator to print a fraction to an output stream in the format “numerator/denominator”.
* The >> operator to read a fraction from an input stream by taking two integers as input. 
* All operators should work on both sides on fractions and floats type variables. on a float var you need use up to 3 digits beyond the desimal point for acuracy.  

דוגמאות לפעולת המחלקה ניתן למצוא ב-[Demo.cpp](Demo.cpp).

בשלב א עליכם לכתוב כותרות ובדיקות-יחידה מקיפות. 

כיתבו את כל הקבצים הדרושים כך שהפקודות הבאות יעבדו ללא שגיאות:

<div dir='ltr'>

    make demo && ./demo
	make test && ./test

</div>

מומלץ גם להריץ:

<div dir='ltr'>

    make tidy
    make valgrind

</div>

שימו לב:
אין לשנות קבצים קיימים, אלא רק להוסיף קבצים חדשים.
מערכת הבדיקה האוטומטית מעתיקה מחדש את כל הקבצים הקיימים על-גבי הפתרון שאתם מגישים,
ולכן כל שינוי שתעשו בקבצים הקיימים יימחק.

בהצלחה
</div>
