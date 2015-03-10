//
//  RMXData.swift
//  Metal 3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation

struct RMXData {
    private static var i: Int = 0
    static var count: Int {
        ++i
        return i-1
    }
}