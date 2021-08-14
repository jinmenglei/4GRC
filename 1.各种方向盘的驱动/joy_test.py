# coding:utf-8
import pygame

# 白底黑字
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)


# This is a simple class that will help us print to the screen
# 这是一个简单的类,它将帮助我们打印到屏幕上
# It has nothing to do with the joysticks, just outputting the information.
# 它与操纵杆无关,只是输出信息。
class TextPrint:
    def __init__(self):
        self.reset()
        self.font = pygame.font.Font(None, 20)

    def defprint(self, screen, textString):
        textBitmap = self.font.render(textString, True, BLACK)
        screen.blit(textBitmap, [self.x, self.y])
        self.y += self.line_height

    def reset(self):
        self.x = 10
        self.y = 10
        self.line_height = 15

    def indent(self):
        self.x += 10

    def unindent(self):
        self.x -= 10


pygame.init()

# Set the width and height of the screen [width,height]
# 设置屏幕的宽度和高度(宽度、高度)
size = [500, 700]
screen = pygame.display.set_mode(size)  # 屏幕、显示、样式

pygame.display.set_caption("joy test")  # 标题

# Loop until the user clicks the close button.
# 循环，直到用户点击关闭按钮。
done = False

# Used to manage how fast the screen updates
# 用来管理屏幕更新的速度
clock = pygame.time.Clock()

# Initialize the joysticks
# 初始化操纵杆
pygame.joystick.init()

# Get ready to print
# 准备打印
textPrint = TextPrint()

# -------- Main Program Loop 主循环程序-----------
while done == False:
    # EVENT PROCESSING STEP
    # 事件处理步骤
    for event in pygame.event.get():  # User did something用户做了什么
        if event.type == pygame.QUIT:  # If user clicked close如果用户点击关闭
            done = True  # Flag that we are done so we exit this loop
            # 标记我们已经完成，所以我们退出这个循环

        # Possible joystick actions: JOYAXISMOTION JOYBALLMOTION JOYBUTTONDOWN JOYBUTTONUP JOYHATMOTION
        # 可能的操纵杆动作:             轴              球           按钮                      帽子
        if event.type == pygame.JOYBUTTONDOWN:
            print("Joystick button pressed.")  # 操纵杆按钮按下
        if event.type == pygame.JOYBUTTONUP:
            print("Joystick button released.")  # 操纵杆按钮解除

    # DRAWING STEP 绘图设置
    # First, clear the screen to white. Don't put other drawing commands
    # 首先，  将屏幕显示为白色，        不要输入其他绘图命令
    # above this, or they will be erased with this command.
    # 否则           他们将会被这个命令抹去。
    screen.fill(WHITE)
    textPrint.reset()

    # Get count of joysticks获得操纵杆的数量
    joystick_count = pygame.joystick.get_count()  # 数量

    textPrint.defprint(screen, "Number of joysticks: {}".format(joystick_count))  # 格式
    textPrint.indent()  # 缩进

    # For each joystick: 遍历每个操纵杆
    for i in range(joystick_count):  # 范围
        joystick = pygame.joystick.Joystick(i)  # 新建一个 Joystick 对象
        joystick.init()  # 初始化 joystick 模块

        textPrint.defprint(screen, "Joystick {}".format(i))
        textPrint.indent()  # 初始化 joystick 模块

        # Get the name from the OS for the controller/joystick
        # 从操作系统中找到操纵杆的名字
        name = joystick.get_name()  # 获得 Joystick 系统名称
        textPrint.defprint(screen, "Joystick name: {}".format(name))

        # Usually axis run in pairs, up/down for one, and left/right for the other.
        # 通常轴成对运行，一个向上 / 向下，另一个向左 / 向右
        axes = joystick.get_numaxes()  # 获得 Joystick 操纵轴的数量
        textPrint.defprint(screen, "Number of axes: {}".format(axes))
        textPrint.indent()

        for i in range(axes):
            axis = joystick.get_axis(i)  # 获得操纵轴的当前坐标
            textPrint.defprint(screen, "Axis {} value: {:>6.3f}".format(i, axis))
            #:>6.3f ：总长度为6位,精确到小数点后三位的浮点类型
        textPrint.unindent()  # 不缩进

        buttons = joystick.get_numbuttons()  # 获得 Joystick 上追踪球的数量
        textPrint.defprint(screen, "Number of buttons: {}".format(buttons))
        textPrint.indent()

        for i in range(buttons):
            button = joystick.get_button(i)  # 获得当前按钮的状态。
            textPrint.defprint(screen, "Button {:>2} value: {}".format(i, button))
        textPrint.unindent()

        # Hat switch. All or nothing for direction, not like joysticks.
        # 帽子开关， 要么全有，要么没有，          不像操纵杆
        # Value comes back in an array.
        # 值返回到数组中。
        hats = joystick.get_numhats()  # 获得 Joystick 上帽键的数量
        textPrint.defprint(screen, "Number of hats: {}".format(hats))
        textPrint.indent()

        for i in range(hats):
            hat = joystick.get_hat(i)  # 获得 Joystick 上帽键的位置
            textPrint.defprint(screen, "Hat {} value: {}".format(i, str(hat)))
        textPrint.unindent()

        textPrint.unindent()

    # ALL CODE TO DRAW SHOULD GO ABOVE THIS COMMENT
    # 所有要绘制的代码都应该超过这个注释
    # Go ahead and update the screen with what we've drawn.
    # 继续用我们绘制的图像更新屏幕。
    pygame.display.flip()

    # Limit to 20 frames per second
    # 最多20个帧率
    clock.tick(20)

# Close the window and quit.
# 关上窗口，退出
# If you forget this line, the program will 'hang'
# 如果你忘了这一行，程序会“挂起”
# on exit if running from IDLE.
# 在退出，如果从IDLE运行
pygame.quit()  # 卸载 joystick 模块



