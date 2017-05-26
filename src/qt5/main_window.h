/*
  RPCEmu - An Acorn system emulator

  Copyright (C) 2016-2017 Matthew Howkins

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "configure_dialog.h"
#include "network_dialog.h"
#include "rpc-qt5.h"

#include "rpcemu.h"

class QAction;
class QLabel;
class QMenu;

class MainLabel : public QLabel
{
	Q_OBJECT

public:
	MainLabel(Emulator &emulator);

protected:
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
	Emulator &emulator;
};
     
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(Emulator &emulator);
	virtual ~MainWindow();
	QLabel *label;

protected:
	void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
	void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private slots:
	void menu_reset();
	void menu_loaddisc0();
	void menu_loaddisc1();
	void menu_configure();
	void menu_networking();
	void menu_fullscreen();
	void menu_cpu_idle();
	void menu_cdrom_disabled();
	void menu_cdrom_empty();
	void menu_cdrom_iso();
	void menu_mouse_hack();
	void menu_mouse_capture();
	void menu_mouse_twobutton();
	void menu_online_manual();
	void menu_visit_website();
	void menu_about();

	void main_display_update(QPixmap pixmap);

	// MIPS counting
	void mips_timer_timeout();

signals:
        void main_display_signal(QPixmap);

private:
	void create_actions();
	void create_menus();
	void create_tool_bars();
	void create_status_bar();

	void readSettings();
	void writeSettings();

	bool full_screen;

	QImage *image;

	QString curFile;

	// Menus
	QMenu *file_menu;
	QMenu *disc_menu;
	QMenu *settings_menu;
	QMenu *cdrom_menu;
	QMenu *mouse_menu;
	QMenu *help_menu;

	// Actions on File menu
	QAction *reset_action;
	QAction *exit_action;

	// Actions on Disc menu
	QAction *loaddisc0_action;
	QAction *loaddisc1_action;

	// Actions on Settings menu (and submenus)
	QAction *configure_action;
	QAction *networking_action;
	QAction *fullscreen_action;
	QAction *cpu_idle_action;
	QAction *cdrom_disabled_action;
	QAction *cdrom_empty_action;
	QAction *cdrom_iso_action;
	QAction *mouse_hack_action;
	QAction *mouse_capture_action;
	QAction *mouse_twobutton_action;

	// Actions on About menu
	QAction *online_manual_action;
	QAction *visit_website_action;
	QAction *about_action;

	// Dialogs
	ConfigureDialog *configure_dialog;
	NetworkDialog *network_dialog;

	// Pointer to emulator instance
	Emulator &emulator;

	// GUI thread copy of the emulator's config
	Config config_copy;
	Model model_copy;

	// MIPS counting
	QTimer mips_timer;
	uint64_t mips_total_instructions;
	int32_t mips_seconds;
	QString window_title;
};

#endif