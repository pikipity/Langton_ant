兰顿蚂蚁
===========

用 Ncurses 写的一个兰顿蚂蚁的程序。

### 程序效果：

![兰顿蚂蚁](https://lh6.googleusercontent.com/-8Ofjz3znllU/UtgDNKOpL6I/AAAAAAAABbk/4VOba8xKl1E/s648/1.gif)

### [兰顿蚂蚁 Wikipedia 介绍](http://zh.wikipedia.org/wiki/%E5%85%B0%E9%A1%BF%E8%9A%82%E8%9A%81)

兰顿蚂蚁是细胞自动机的例子。它由克里斯托夫·兰顿提出。

在平面上的正方形格被填上黑色或白色。在其中一格正方形有一只“蚂蚁”。它的头部朝向上下左右其中一方。蚂蚁走过的格子颜色改变。

+ 若蚂蚁在黑格，右转90度，将该格改为白格，向前移一步；
+ 若蚂蚁在白格，左转90度，将该格改为黑格，向前移一步。

很多时，蚂蚁刚刚开始时留下的路线都会有接近对称，像是会重复。但不论起始状态如何，蚂蚁的路线必然是无限长的。