# CG/hfut/合肥工业大学计算机图形学实验及大作业
<br>实验一
<br>实现了DDA算法和Mid_bresenham算法以及二者的性能比较，因为实现了性能比较，所以下载后需要手动解除掉DDA和Mid_bresenham算法函数中的注释才能生效
<br>这里性能比较的时候需要将相关算法的函数实现中的DrawPixel绘制像素的函数给注释掉，才能很好的体现二者的性能差距
<br>关于性能比较的修改部分在OnDraw函数中
<br>
<br>实验二
<br>实现了x-扫描线算法和有效边表算法
<br>这里也可以进行性能比较，同样也是需要注释掉DrawPixel函数
<br>
<br>实验三
<br>主要是配置环境的问题，我不知道为什么使用老师给的环境包不行，说32位的64位用不了，后面在vs中的Nuget中下载了nupengl包就可以成功解决，这里上传的项目文件中已经包含了该包
<br>
<br>大作业
<br>实现了简单的mesh模型展示和简单的交互，这里的文件路径是通过命令行参数传入的，也可以在main函数的注释部分添加
<br>这里的交互实现了鼠标旋转，右键恢复，滚轮缩放，但是缩放之后未重新计算法向量，故会发生过曝和过暗的现象，如果后面有时间会更新一下这个地方;键盘wsadqe实现上下左右里外的平移
<br>已修改过曝过暗问题
<br>
<br>这里就不放图片了，下载后应该可以直接编译运行的
<br>
<br>
<br>
<br>
<br>
<br>
