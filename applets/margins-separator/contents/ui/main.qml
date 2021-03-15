/*
 * Copyright 2020 Niccolò Venerandi <niccolo@venerandi.com>
 * Copyright 2019 Chris Holland <zrenfire@gmail.com>
 * Copyright 2014 Ashish Madeti <ashishmadeti@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

import QtQuick 2.4
import QtQuick.Layouts 1.0
import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.extras 2.0 as PlasmaExtras

Item {
    id: root
    
    //--- containment.editMode detector from Show Desktop (Win7)
    property var containmentInterface: null
    readonly property bool editMode: containmentInterface ? containmentInterface.editMode : false
    onParentChanged: {
        if (parent) {
            for (var obj = root, depth = 0; !!obj; obj = obj.parent, depth++) {
                // console.log('depth', depth, 'obj', obj)
                if (obj.toString().startsWith('ContainmentInterface')) {
                    // desktop containment / plasmoidviewer
                    // Note: This doesn't always work. FolderViewDropArea may not yet have
                    //       ContainmentInterface as a parent when this loop runs.
                    if (typeof obj['editMode'] === 'boolean') {
                        // console.log('\t', 'obj.editMode', obj.editMode, typeof obj['editMode'])
                        root.containmentInterface = obj
                        break
                    }
                } else if (obj.toString().startsWith('DeclarativeDropArea')) {
                    // panel containment
                    if (typeof obj['Plasmoid'] !== 'undefined' && obj['Plasmoid'].toString().startsWith('ContainmentInterface')) {
                        if (typeof obj['Plasmoid']['editMode'] === 'boolean') {
                            // console.log('\t', 'obj.Plasmoid', obj.Plasmoid, typeof obj['Plasmoid']) // ContainmentInterface
                            // console.log('\t', 'obj.Plasmoid.editMode', obj.Plasmoid.editMode, typeof obj['Plasmoid']['editMode'])
                            root.containmentInterface = obj.Plasmoid
                            break
                        }
                    }
                }
            }
        }
    }
    
    Layout.minimumWidth:   root.editMode ? units.largeSpacing : 1
    Layout.preferredWidth: Layout.minimumWidth
    Layout.maximumWidth:   Layout.minimumWidth

    Layout.minimumHeight: Layout.minimumWidth
    Layout.preferredHeight: Layout.minimumHeight
    Layout.maximumHeight: Layout.minimumHeight

    Plasmoid.constraintHints: PlasmaCore.Types.MarginAreasSeparator
    Plasmoid.preferredRepresentation: Plasmoid.fullRepresentation
}
