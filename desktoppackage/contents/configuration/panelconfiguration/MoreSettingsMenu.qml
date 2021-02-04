/*
 *  Copyright 2013 Marco Martin <mart@kde.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  2.010-1301, USA.
 */

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.12 as QQC2
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.extras 2.0 as PlasmaExtras
import org.kde.plasma.core 2.0 as PlasmaCore

PlasmaComponents.Menu {
    id: contextMenu

    PlasmaComponents.MenuItem {
        text: i18nd("plasma_shell_org.kde.plasma.desktop", "Panel Alignment")
        section: true
    }

    property var eg1: PlasmaComponents.ExclusiveGroup { id: eg1 }

    PlasmaComponents.MenuItem {
        text: panel.formFactor === PlasmaCore.Types.Vertical ? i18nd("plasma_shell_org.kde.plasma.desktop", "Top") : i18nd("plasma_shell_org.kde.plasma.desktop", "Left")
        checked: panel.alignment === Qt.AlignLeft
        checkable: true
        exclusiveGroup: eg1
        onClicked: panel.alignment = Qt.AlignLeft
    }
    PlasmaComponents.MenuItem {
        text: i18nd("plasma_shell_org.kde.plasma.desktop", "Center")
        checked: panel.alignment === Qt.AlignCenter
        checkable: true
        exclusiveGroup: eg1
        onClicked: panel.alignment = Qt.AlignCenter
    }
    PlasmaComponents.MenuItem {
        text: panel.formFactor === PlasmaCore.Types.Vertical ? i18nd("plasma_shell_org.kde.plasma.desktop", "Bottom") : i18nd("plasma_shell_org.kde.plasma.desktop", "Right")
        checked: panel.alignment === Qt.AlignRight
        checkable: true
        exclusiveGroup: eg1
        onClicked: panel.alignment = Qt.AlignRight
    }

    PlasmaComponents.MenuItem {
        text: i18nd("plasma_shell_org.kde.plasma.desktop", "Visibility")
        section: true
    }

    property var eg2: PlasmaComponents.ExclusiveGroup { id: eg2 }

    PlasmaComponents.MenuItem {
        text: i18nd("sectionplasma_shell_org.kde.plasma.desktop", "Always Visible")
        checked: configDialog.visibilityMode === 0
        checkable: true
        exclusiveGroup: eg2
        onClicked: configDialog.visibilityMode = 0
    }
    PlasmaComponents.MenuItem {
        text: i18nd("plasma_shell_org.kde.plasma.desktop", "Auto Hide")
        checked: configDialog.visibilityMode === 1
        checkable: true
        exclusiveGroup: eg2
        onClicked: configDialog.visibilityMode = 1
    }
    PlasmaComponents.MenuItem {
        text: i18nd("plasma_shell_org.kde.plasma.desktop", "Windows Can Cover")
        checked: configDialog.visibilityMode === 2
        checkable: true
        exclusiveGroup: eg2
        onClicked: configDialog.visibilityMode = 2
    }
    PlasmaComponents.MenuItem {
        text: i18nd("plasma_shell_org.kde.plasma.desktop", "Windows Go Below")
        checked: configDialog.visibilityMode === 3
        checkable: true
        exclusiveGroup: eg2
        onClicked: configDialog.visibilityMode = 3
    }

    PlasmaComponents.MenuItem { separator: true }

    PlasmaComponents.MenuItem {
        text: i18nd("plasma_shell_org.kde.plasma.desktop", "Maximize Panel")
        icon: panel.formFactor === PlasmaCore.Types.Vertical ? "zoom-fit-height" : "zoom-fit-width"
        onClicked: panel.maximize()
    }
    PlasmaComponents.MenuItem {
        text: i18nd("plasma_shell_org.kde.plasma.desktop", "Remove Panel")
        icon: "delete"
        onClicked: plasmoid.action("remove").trigger()
    }

    function hide() {
        visible = false;
    }

    Component.onCompleted: {
        dialogRoot.closeContextMenu.connect(hide);
    }
}
