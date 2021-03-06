foo = {
    'name': 'Scenario Name',
    '_floors': {
        'Floor Name': {
            'z': 0,
            '_rooms': {
                'Room Name': {
                    'id': 'RoomID',
                    'x': 9,
                    'y': 1,
                    'walls': {
                        'WallID': {
                            'name': 'Wall Name',
                            'image': 'pool.jpg',
                            '_props': {
                                'cat': {
                                    'name': 'cat',
                                    'image': 'cat.jpg',
                                    'width': 20,
                                    'height': 20,
                                    'top': 0,
                                    'left': 0
                                }
                            },
                            'destination': {
                                'x': 1
                            }
                        }
                    }
                },
                'Another Room': {
                    'id': 'AnotherID',
                    'x': 4,
                    'y': 3,
                    'walls': {
                        'AnotherWall': {
                            'name': 'Another Name',
                            'image': 'img.png',
                        }
                    }
                }
            }
        }
    },
    '_conversations': {
        'Conversation Name': {
            '1': {
                'message': 'Hello',
                'replies': {
                    'Hi': 0
                }
            }
        }
    },
    '_triggers': {
        'Trigger Name': {
            'events': {
                'showModal': ['Hello', 'Modal Text']
            }
        }
    },
    'inactiveProps': ['cat'],
    '_player': {
        'x': 1,
        'y': 1,
        'z': 1,
        '_facing': 'n',
        'inventory': []
    }
};
