
.SUFFIXES :

# default install directories
include INSTALL

#
VERSION := $(shell grep "^version" meld/meldapp.py | cut -d \"  -f 2)
RELEASE := meld-$(VERSION)
MELD_CMD := ./meld #--profile
SPECIALS := bin/meld meld/paths.py
BROWSER := firefox

.PHONY:all
all: $(addsuffix .install,$(SPECIALS)) meld.desktop meld.xml
	$(MAKE) -C po
	$(MAKE) -C help
	chmod 0755 bin/meld.install

.PHONY:clean
clean:
	@find ./meld -type f \( -name '*.pyc' -o -name '*.install' \) -print0 |\
		xargs -0 rm -f
	@find ./bin -type f \( -name '*.install' \) -print0 | xargs -0 rm -f
	@rm -f data/meld.desktop
	@rm -f data/mime/meld.xml
	$(MAKE) -C po clean
	$(MAKE) -C help clean

.PHONY:install
install: $(addsuffix .install,$(SPECIALS)) meld.desktop meld.xml
	mkdir -m 755 -p \
		$(DESTDIR)$(bindir) \
		$(DESTDIR)$(libdir_) \
		$(DESTDIR)$(libdir_)/meld \
		$(DESTDIR)$(libdir_)/meld/ui \
		$(DESTDIR)$(libdir_)/meld/util \
		$(DESTDIR)$(libdir_)/meld/vc \
		$(DESTDIR)$(sharedir_)/ui \
		$(DESTDIR)$(sharedir_)/icons \
		$(DESTDIR)$(sharedir_)/theme/dark/Arrows \
		$(DESTDIR)$(sharedir_)/theme/dark/Buttons \
		$(DESTDIR)$(sharedir_)/theme/dark/Check-Radio \
		$(DESTDIR)$(sharedir_)/theme/dark/Frame-Gap \
		$(DESTDIR)$(sharedir_)/theme/dark/Handles \
		$(DESTDIR)$(sharedir_)/theme/dark/Lines \
		$(DESTDIR)$(sharedir_)/theme/dark/ListHeaders \
		$(DESTDIR)$(sharedir_)/theme/dark/Menu-Menubar \
		$(DESTDIR)$(sharedir_)/theme/dark/Others \
		$(DESTDIR)$(sharedir_)/theme/dark/Panel \
		$(DESTDIR)$(sharedir_)/theme/dark/ProgressBar \
		$(DESTDIR)$(sharedir_)/theme/dark/Range \
		$(DESTDIR)$(sharedir_)/theme/dark/Scrollbars \
		$(DESTDIR)$(sharedir_)/theme/dark/Shadows \
		$(DESTDIR)$(sharedir_)/theme/dark/Spin \
		$(DESTDIR)$(sharedir_)/theme/dark/Tabs \
		$(DESTDIR)$(sharedir_)/theme/dark/Toolbar \
		$(DESTDIR)$(docdir_) \
		$(DESTDIR)$(sharedir)/appdata \
		$(DESTDIR)$(sharedir)/applications \
		$(DESTDIR)$(sharedir)/mime/packages \
		$(DESTDIR)$(sharedir)/pixmaps \
		$(DESTDIR)$(sharedir)/icons/hicolor/16x16/apps \
		$(DESTDIR)$(sharedir)/icons/hicolor/22x22/apps \
		$(DESTDIR)$(sharedir)/icons/hicolor/32x32/apps \
		$(DESTDIR)$(sharedir)/icons/hicolor/48x48/apps \
		$(DESTDIR)$(sharedir)/icons/hicolor/scalable/apps \
		$(DESTDIR)$(sharedir)/icons/HighContrast/scalable/apps \
		$(DESTDIR)$(helpdir_)
	install -m 755 bin/meld.install \
		$(DESTDIR)$(bindir)/meld
	install -m 644 meld/*.py \
		$(DESTDIR)$(libdir_)/meld
	install -m 644 meld/ui/*.py \
		$(DESTDIR)$(libdir_)/meld/ui
	install -m 644 meld/util/*.py \
		$(DESTDIR)$(libdir_)/meld/util
	install -m 644 meld/vc/*.py \
		$(DESTDIR)$(libdir_)/meld/vc
	install -m 644 meld/paths.py.install \
		$(DESTDIR)$(libdir_)/meld/paths.py
	install -m 644 data/meld.desktop \
		$(DESTDIR)$(sharedir)/applications
	install -m 644 data/meld.appdata.xml \
		$(DESTDIR)$(sharedir)/appdata/
	install -m 644 data/mime/meld.xml \
		$(DESTDIR)$(sharedir)/mime/packages/
	$(PYTHON)    -c 'import compileall; compileall.compile_dir("$(DESTDIR)$(libdir_)",10,"$(libdir_)")'
	$(PYTHON) -O -c 'import compileall; compileall.compile_dir("$(DESTDIR)$(libdir_)",10,"$(libdir_)")'
	install -m 644 data/theme/dark/gtkrc \
		$(DESTDIR)$(sharedir_)/theme/dark
	install -m 644 data/theme/dark/applications.rc \
		$(DESTDIR)$(sharedir_)/theme/dark
	install -m 644 data/theme/dark/panel.rc \
		$(DESTDIR)$(sharedir_)/theme/dark
	install -m 644 data/theme/dark/Arrows/* \
		$(DESTDIR)$(sharedir_)/theme/dark/Arrows
	install -m 644 data/theme/dark/Buttons/* \
		$(DESTDIR)$(sharedir_)/theme/dark/Buttons
	install -m 644 data/theme/dark/Check-Radio/* \
		$(DESTDIR)$(sharedir_)/theme/dark/Check-Radio
	install -m 644 data/theme/dark/Frame-Gap/* \
		$(DESTDIR)$(sharedir_)/theme/dark/Frame-Gap
	install -m 644 data/theme/dark/Handles/* \
		$(DESTDIR)$(sharedir_)/theme/dark/Handels
	install -m 644 data/theme/dark/Lines/* \
		$(DESTDIR)$(sharedir_)/theme/dark/Lines
	install -m 644 data/theme/dark/ListHeaders/* \
		$(DESTDIR)$(sharedir_)/theme/dark/ListHeaders
	install -m 644 data/theme/dark/Menu-Menubar/* \
		$(DESTDIR)$(sharedir_)/theme/dark/Menu-Menubar
	install -m 644 data/theme/dark/Others/* \
		$(DESTDIR)$(sharedir_)/theme/dark/Others
	install -m 644 data/theme/dark/Panel/* \
		$(DESTDIR)$(sharedir_)/theme/dark/Panel
	install -m 644 data/theme/dark/ProgressBar/* \
		$(DESTDIR)$(sharedir_)/theme/dark/ProgressBar
	install -m 644 data/theme/dark/Range/* \
		$(DESTDIR)$(sharedir_)/theme/dark/Range
	install -m 644 data/theme/dark/Scrollbars/* \
		$(DESTDIR)$(sharedir_)/theme/dark/Scrollbars
	install -m 644 data/theme/dark/Shadows/* \
		$(DESTDIR)$(sharedir_)/theme/dark/Shadows
	install -m 644 data/theme/dark/Spin/* \
		$(DESTDIR)$(sharedir_)/theme/dark/Spin
	install -m 644 data/theme/dark/Tabs/* \
		$(DESTDIR)$(sharedir_)/theme/dark/Tabs
	install -m 644 data/theme/dark/Toolbar/* \
		$(DESTDIR)$(sharedir_)/theme/dark/Toolbar
	install -m 644 \
		data/ui/*.ui \
		$(DESTDIR)$(sharedir_)/ui
	install -m 644 \
		data/ui/*.xml \
		$(DESTDIR)$(sharedir_)/ui
	install -m 644 \
		data/icons/*.xpm \
		data/icons/*.png \
		$(DESTDIR)$(sharedir_)/icons
	install -m 644 data/icons/hicolor/16x16/apps/meld.png \
		$(DESTDIR)$(sharedir)/icons/hicolor/16x16/apps/meld.png
	install -m 644 data/icons/hicolor/22x22/apps/meld.png \
		$(DESTDIR)$(sharedir)/icons/hicolor/22x22/apps/meld.png
	install -m 644 data/icons/hicolor/32x32/apps/meld.png \
		$(DESTDIR)$(sharedir)/icons/hicolor/32x32/apps/meld.png
	install -m 644 data/icons/hicolor/48x48/apps/meld.png \
		$(DESTDIR)$(sharedir)/icons/hicolor/48x48/apps/meld.png
	install -m 644 data/icons/hicolor/scalable/apps/meld.svg \
		$(DESTDIR)$(sharedir)/icons/hicolor/scalable/apps/meld.svg
	install -m 644 data/icons/HighContrast/scalable/apps/meld.svg \
		$(DESTDIR)$(sharedir)/icons/HighContrast/scalable/apps/meld.svg
	$(MAKE) -C po install
	$(MAKE) -C help install
	$(update_mime_database)
	$(update_desktop_database)

.PHONY:install-glade-support
install-glade-support:
	install -m 644 meld/ui/gladesupport.py \
		$(DESTDIR)$(libdir)/glade3/modules/meld.py
	install -m 644 meld/ui/catalog.xml \
		$(DESTDIR)$(sharedir)/glade3/catalogs/meld.xml

.PHONY:glade
glade:
	PYTHONPATH="${PYTHONPATH}:/usr/lib/glade3/modules/" glade-3

meld.desktop: data/meld.desktop.in
	intltool-merge -d po data/meld.desktop.in data/meld.desktop

meld.xml: data/mime/meld.xml.in
	intltool-merge -d po data/mime/meld.xml.in data/mime/meld.xml

%.install: %
	$(PYTHON) tools/install_paths \
		libdir=$(libdir_) \
		localedir=$(localedir) \
		helpdir=$(helpdir_) \
		sharedir=$(sharedir_) \
		< $< > $@

.PHONY:uninstall
uninstall:
	-rm -rf \
		$(sharedir_) \
		$(docdir_) \
		$(helpdir_) \
		$(libdir_) \
		$(bindir)/meld \
		$(sharedir)/applications/meld.desktop \
		$(sharedir)/appdata/meld.appdata.xml \
		$(sharedir)/mime/packages/meld.xml \
		$(sharedir)/pixmaps/meld.png
	$(MAKE) -C po uninstall
	$(MAKE) -C help uninstall
	$(update_mime_database)
	$(update_desktop_database)

update_mime_database_cmd = update-mime-database $(sharedir)/mime
update_mime_database = \
	@-if test -z "$(DESTDIR)"; then \
		echo "Updating MIME database."; \
		$(update_mime_database_cmd); \
	else \
		echo "*** MIME database not updated.  After (un)install, run this:"; \
		echo "***   $(update_mime_database_cmd)"; \
	fi

update_desktop_database_cmd = update-desktop-database $(sharedir)/applications
update_desktop_database = \
	@-if test -z "$(DESTDIR)"; then \
		echo "Updating desktop database."; \
		$(update_desktop_database_cmd); \
	else \
		echo "*** Desktop database not updated.  After (un)install, run this:"; \
		echo "***   $(update_desktop_database_cmd)"; \
	fi
