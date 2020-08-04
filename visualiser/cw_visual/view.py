from typing import List, Dict, Tuple
from dataclasses import dataclass
import os

from PySide2.QtWidgets import QApplication, QWidget, QScrollArea, QHBoxLayout, QVBoxLayout, QSizePolicy, QScrollBar, QLabel
from PySide2.QtGui import QPainter, QPen, QBrush, QColor, QPainterPath, QTransform, QPixmap, QFontMetrics, QFont
from PySide2.QtCore import QObject, QRect, QRectF, QPoint, QPointF, Slot, Signal, Qt, QTimer, QSize, QSettings

from cw_visual.colors import *
from cw_visual.ui_widgets import *


def pairs(string):
    it = iter(string)
    try:
        while True:
            a = next(it)
            b = next(it)
            yield a, b
    except StopIteration:
        pass


class MouseScrolledArea(QScrollArea):
    """scroll area that can be scrolled with mouse drag"""

    def mousePressEvent(self, ev):
        self.mouse_last_pos = ev.pos()

    def mouseMoveEvent(self, ev):  # mouse move only triggered when a mouse button pressed
        dmouse = ev.pos() - self.mouse_last_pos
        self.scrollContent(-dmouse.x(), -dmouse.y())
        self.mouse_last_pos = ev.pos()

    def scrollContent(self, dx, dy):
        horizontal = self.horizontalScrollBar()
        vertical = self.verticalScrollBar()

        v_value = vertical.value()
        h_value = horizontal.value()

        horizontal.setValue(h_value + dx)
        vertical.setValue(v_value + dy)


class NotifyScrollbar(QScrollBar):
    """scrollbar that notifies when hidden or shown """

    shown = Signal(bool)

    def showEvent(self, event):
        self.shown.emit(True)

    def hideEvent(self, event):
        self.shown.emit(False)


class ScrollsOverContentArea(MouseScrolledArea):
    """ makes scrollbars shown above content
        only to improve ui design
    """
    scrollsWidth = 8  # should follow up with your design

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.setVerticalScrollBar(NotifyScrollbar())
        self.setHorizontalScrollBar(NotifyScrollbar())

        self.verticalScrollBar().shown.connect(self.vertical_scrollbar_shown)
        self.horizontalScrollBar().shown.connect(self.horizontal_scrollbar_shown)

    def vertical_scrollbar_shown(self, shown):
        m = self.viewportMargins()
        l = m.left()
        t = m.top()
        b = m.bottom()

        if shown:
            # make scrollbars above content
            self.setViewportMargins(l, t, -self.scrollsWidth, b)
        else:
            # restore vieport margins
            self.setViewportMargins(l, t, 0, b)

    def horizontal_scrollbar_shown(self, shown):
        m = self.viewportMargins()
        l = m.left()
        t = m.top()
        r = m.right()

        if shown:
            # make scrollbars above content
            self.setViewportMargins(l, t, r, -self.scrollsWidth)
        else:
            # restore vieport margins
            self.setViewportMargins(l, t, r, 0)

    def sizeHint(self):
        """use size hint of the child widget"""
        return self.widget().sizeHint()

    def center_view(self):
        vertical = self.verticalScrollBar()
        horizontal = self.horizontalScrollBar()

        ScrollsOverContentArea.center_scrollbar(horizontal)
        ScrollsOverContentArea.center_scrollbar(vertical)

    @staticmethod
    def center_scrollbar(scrollbar: QScrollBar):
        min = scrollbar.minimum()
        max = scrollbar.maximum()

        scrollbar.setValue((max - min) // 2)


class View(QWidget):
    key_pressed = Signal(str)

    def __init__(self, parent=None):
        super().__init__(parent)
        self.first_show = True  # to apply center view on byte view
        self.players_count = 0
        self.player_widgets = []

        self.setWindowTitle("corewar visual")

        self.byte_view = ByteView()

        self.scroll_area = ScrollsOverContentArea()
        self.scroll_area.setWidget(self.byte_view)

        self.layout = QHBoxLayout()
        self.layout.addStretch()  # add left stretch to main layout to center all content
        self.layout.addWidget(self.scroll_area)

        self.add_ui()
        self.layout.addStretch()  # add right stretch to main layout to center all content

        self.setLayout(self.layout)

        self.style()

        # make references to byte_view functions availible on self
        self.draw_cursor_rect = self.byte_view.draw_cursor_rect
        self.erase_cursor_rect = self.byte_view.erase_cursor_rect
        self.write_bytes = self.byte_view.write_bytes
        self.print_msg = self.byte_view.print_msg
        self.set_paused = self.game_info.set_paused
        self.set_cycle = self.game_info.set_cycle
        self.set_speed = self.game_info.set_speed

        self.readSettings()

    def add_ui(self):
        grid = QGridLayout()
        grid.setSpacing(8)
        grid.setAlignment(Qt.AlignVCenter | Qt.AlignLeft)

        # unpack widgets to put them into one grid layout
        self.game_info = GameInfo()
        widget = iter(self.game_info)

        grid.addWidget(next(widget), 0, 0)
        grid.addWidget(next(widget), 1, 0)
        grid.addWidget(next(widget), 1, 1)
        grid.addWidget(next(widget), 2, 0)
        grid.addWidget(next(widget), 2, 1)

        grid.setRowMinimumHeight(3, 20)

        player1 = PlayerInfo(1)
        i = self.unpack_player_widget_to_grid(player1, grid, 4)

        player2 = PlayerInfo(2)
        i = self.unpack_player_widget_to_grid(player2, grid, i + 1)

        player3 = PlayerInfo(3)
        i = self.unpack_player_widget_to_grid(player3, grid, i + 1)

        player4 = PlayerInfo(4)
        i = self.unpack_player_widget_to_grid(player4, grid, i + 1)

        player1.set_visible(False)
        player2.set_visible(False)
        player3.set_visible(False)
        player4.set_visible(False)

        self.player_widgets = [player1, player2, player3, player4]

        grid.setColumnMinimumWidth(1, 100)
        grid.setContentsMargins(20, 20, 20, 20)
        self.layout.addLayout(grid)

    def unpack_player_widget_to_grid(self, widget, grid, i):
        widget = iter(widget)

        grid.addWidget(next(widget), i, 0)
        grid.addWidget(next(widget), i, 1)
        grid.addWidget(next(widget), i+1, 0)
        grid.addWidget(next(widget), i+1, 1)

        grid.setRowMinimumHeight(i+2, 20)

        return i+3

    def style(self):
        self.layout.setContentsMargins(0, 0, 0, 0)
        self.layout.setSpacing(0)

        self.scroll_area.setAlignment(Qt.AlignVCenter | Qt.AlignRight)

        # path relative to current file otherwise crash when main.py called from different working dir
        dirname = os.path.dirname(__file__)
        stylesheet_path = os.path.join(dirname, 'stylesheet.qss')

        with open(stylesheet_path) as file:
            stylesheet = file.read()

        self.setObjectName("main")  # for proper styling
        self.setStyleSheet(stylesheet)

    def keyPressEvent(self, ev):
        if ev.key() == Qt.Key_Space:
            self.key_pressed.emit(" ")
        elif ev.key() == Qt.Key_D:
            self.key_pressed.emit("d")
        elif ev.key() == Qt.Key_Plus:
            self.key_pressed.emit("+")
        elif ev.key() == Qt.Key_Minus:
            self.key_pressed.emit("-")
        elif ev.key() == Qt.Key_F11:
            self.toggle_fullscreen()
        elif ev.key() == Qt.Key_Return and ev.modifiers() & Qt.AltModifier:
            self.toggle_fullscreen()
        elif ev.key() == Qt.Key_Escape:
            self.exit_fullscreen()

    def toggle_fullscreen(self):
        if self.isFullScreen():
            self.exit_fullscreen()
        else:
            self.enter_fullscreen() 

    def enter_fullscreen(self):
        wstate = self.windowState()
        self.setWindowState(wstate | Qt.WindowFullScreen)
    
    def exit_fullscreen(self):
        wstate = self.windowState()
        self.setWindowState(wstate & (~Qt.WindowFullScreen))

    def showEvent(self, evt):
        if self.first_show:
            self.scroll_area.center_view()
            self.first_show = False

    def closeEvent(self, evt):
        self.writeSettings()

    def readSettings(self):
        # restore window position
        settings = QSettings("settings.ini", QSettings.IniFormat)
        screen_rect = QApplication.desktop().screenGeometry()
        default_rect = QRect(
            screen_rect.width() // 6,
            screen_rect.height() // 4,
            screen_rect.width() * 2 // 3,
            screen_rect.height() // 2
        )
        geometry = settings.value("geometry", default_rect)
        self.setGeometry(geometry)

        maximized = settings.value("maximized", False)
        fullscreen = settings.value("fullscreen", False)
        wstate = self.windowState()

        if fullscreen == "true":
            self.setWindowState(wstate | Qt.WindowFullScreen)
        elif maximized:
            self.setWindowState(wstate | Qt.WindowMaximized)


    def writeSettings(self):
        # remeber window position
        settings = QSettings("settings.ini", QSettings.IniFormat)

        if not (self.isMaximized() or self.isFullScreen()):
            settings.setValue("geometry", self.geometry())

        settings.setValue("maximized", self.isMaximized())
        settings.setValue("fullscreen", self.isFullScreen())

    def add_player(self, name: str):
        index = self.players_count

        player = self.player_widgets[index]

        player.set_visible(True)
        player.set_name(name)

        self.players_count += 1

    def set_cursor_count(self, pl_number, count):
        player: PlayerInfo = self.player_widgets[pl_number]
        player.set_cursors_count(count)

    def declare_winner(self, number: int):
        winner = self.player_widgets[number]
        winner.declare_winner()

        for player in self.player_widgets:
            if player is not winner:
                player.declare_loser()

        self.game_info.set_game_finished()


@dataclass
class MsgLines:
    """
    is used to remember lines occupied by msgs printed to byteview
    in oreder to clear them when new one is going to be printed
    """
    start_line: int
    line_count: int


class ByteView(QWidget):
    """
    Is used to draw memory, players and cursors state onto a widget
    """
    byte_margin = 0
    byte_padding = 4

    test_curr_addr = 0

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.initialize()
        self.startTimer(1000/60)

    def initialize(self):
        font_size = compute_font_size()

        font = QApplication.font()
        font.setPixelSize(font_size)
        # font.setBold(True)
        self.font = font

        self.font_bold = QFont(font)
        self.font_bold.setBold(True)

        self.byte_rect = self.compute_byte_rect()
        self.byte_advance = self.compute_byte_advance()
        self.bytes_pixmap = self.create_pixmap(transparent=False)
        self.bytes_field = self.build_bytes_field()
        self.cursors_pixmap = self.create_pixmap(transparent=True)

        self.setMinimumWidth(self.bytes_pixmap.width())
        self.setMinimumHeight(self.bytes_pixmap.height())

        self.render_empty_bytes_to_pixmap()

        self.prev_msg_lines = MsgLines(0, 0)

    def sizeHint(self):
        return QSize(self.bytes_pixmap.width(), self.bytes_pixmap.height())

    def compute_byte_rect(self):
        fm = QFontMetrics(self.font)
        byte_rect = fm.boundingRect("00")
        byte_rect.moveTopLeft(QPoint())

        return byte_rect.adjusted(-self.byte_padding, 0, self.byte_padding, 0)

    def compute_byte_advance(self):
        fm = QFontMetrics(self.font)
        # return fm.horizontalAdvance("00") + 2*self.byte_padding + self.byte_margin
        return fm.boundingRect("00").width() + 2*self.byte_padding + self.byte_margin

    def create_pixmap(self, transparent=False):
        w = self.byte_advance * 64
        h = self.byte_rect.height() * 64

        pixmap = QPixmap(w, h)

        if transparent:
            pixmap.fill(Qt.transparent)

        return pixmap

    def build_bytes_field(self):
        l = []
        for _ in range(4096):
            l.append(["00", PEN_EMPTY])

        return l

    def render_empty_bytes_to_pixmap(self, address=0, count=4096):
        pixmap_painter = QPainter(self.bytes_pixmap)
        pixmap_painter.setFont(self.font)

        self.print_to_pixmap(pixmap_painter, address, "00"*count, PEN_EMPTY)

        pixmap_painter.end()

    def byte_index(self, byte_addr):
        while True:
            looped_addr = byte_addr % 4096
            i = looped_addr % 64
            j = looped_addr // 64
            yield i, j
            byte_addr += 1

    def write_bytes(self, addr, bytes_str, pen):
        pixmap_painter = QPainter(self.bytes_pixmap)
        pixmap_painter.setFont(self.font)

        self.print_to_pixmap(pixmap_painter, addr, bytes_str, pen)
        pixmap_painter.end()

        self.print_to_bytes_field(addr, bytes_str, pen)

    def print_to_pixmap(self, painter, byte_addr, string, pen):
        index = self.byte_index(byte_addr)
        byte_rect = QRect(self.byte_rect)
        h = byte_rect.height()

        painter.setBrush(BRUSH_EMPTY)

        for digit1, digit2 in pairs(string):
            i, j = next(index)
            txt = digit1 + digit2

            byte_rect.moveTopLeft(QPoint(i*self.byte_advance, j*h))
            painter.setPen(Qt.NoPen)
            painter.drawRect(byte_rect)

            painter.setPen(pen)
            painter.drawText(byte_rect, Qt.AlignCenter, f'{txt}')

    def print_to_bytes_field(self, byte_addr, bytes_str, pen):
        for digit1, digit2 in pairs(bytes_str):
            looped_addr = byte_addr % 4096
            txt = digit1 + digit2
            cell = self.bytes_field[looped_addr]
            cell[0] = txt
            cell[1] = pen
            byte_addr += 1

    def clear_last_msg(self):
        # clear prev msg
        prev_msg_start = self.prev_msg_lines.start_line * 64
        prev_msg_bytes_count = self.prev_msg_lines.line_count * 64

        self.render_empty_bytes_to_pixmap(prev_msg_start, prev_msg_bytes_count)

    def print_msg(self, multiline_msg: str, pens_dict={}):
        """
        prints msg to byte cells vertically and horizontally centered
        pens_dict specifies PEN to be used for specified line 
        eg {0: PEN_WARNING} - line 0 will be painted with PEN_WARNING pen
        """
        self.clear_last_msg()

        pixmap_painter = QPainter(self.bytes_pixmap)
        pixmap_painter.setFont(self.font_bold)

        lines = multiline_msg.splitlines()
        row = 64 // 2 - len(lines) // 2  # centered vertically

        # for clearing this msg when new one printed
        self.prev_msg_lines = MsgLines(row, len(lines))

        for index, line in enumerate(lines):
            line = line.upper()
            line = line.replace(' ', '_')
            if len(line) % 2:  # odd
                line += '_'

            column = 64 // 2 - len(line) // 2 // 2  # centered horizontally
            address = row * 64 + column

            pen = pens_dict.get(index, PEN_LIGHT)
            self.print_to_pixmap(pixmap_painter, address, line, pen)
            row += 1

    def draw_cursor_rect(self, pos: Tuple[int, int], brush, addr):
        painter = QPainter(self.cursors_pixmap)

        cursor_rect = QRect(self.byte_rect)
        h = cursor_rect.height()
        i, j = pos

        cursor_rect.moveTopLeft(QPoint(i*self.byte_advance, j*h))

        painter.setPen(Qt.NoPen)
        painter.setBrush(brush)
        painter.drawRect(cursor_rect)

        painter.setFont(self.font)
        txt = self.bytes_field[addr][0]
        painter.setPen(PEN_BCK)
        painter.drawText(cursor_rect, Qt.AlignCenter, f'{txt}')

        painter.end()

    def erase_cursor_rect(self, pos: Tuple[int, int]):
        painter = QPainter(self.cursors_pixmap)

        cursor_rect = QRect(self.byte_rect)
        h = cursor_rect.height()
        i, j = pos

        cursor_rect.moveTopLeft(QPoint(i*self.byte_advance, j*h))

        painter.setCompositionMode(QPainter.CompositionMode_Source)
        painter.setPen(Qt.NoPen)
        painter.setBrush(Qt.transparent)
        painter.drawRect(cursor_rect)
        painter.setCompositionMode(QPainter.CompositionMode_SourceOver)

    def paintEvent(self, event):
        painter = QPainter(self)

        # clear background
        painter.setBackground(QCOLOR_BKG_EMPTY)
        painter.eraseRect(self.rect())

        # draw memory view layer
        painter.drawPixmap(QPoint(), self.bytes_pixmap)

        # draw cursors layer
        painter.drawPixmap(QPoint(), self.cursors_pixmap)

    def timerEvent(self, event):
        # render pixmaps to widget
        self.update()

def compute_font_size():
    screen_rect = QApplication.desktop().availableGeometry()

    font_size = 14

    while True:
        font = QApplication.font()
        font.setPixelSize(font_size)
        fm = QFontMetrics(font)

        byte_height = fm.boundingRect("0").height()
        byte_view_height = byte_height * 64

        if byte_view_height < screen_rect.height():
            return font_size
        else:
            font_size -= 1