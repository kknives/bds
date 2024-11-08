const std = @import("std");

// Reverse a singly-linked list
fn reverse_internal(comptime T: type, wrapped_node: ?*std.SinglyLinkedList(T).Node) *std.SinglyLinkedList(T).Node {
    const node = wrapped_node.?;
    if (node.next == null) return node;
    var tail = reverse_internal(T, node.next);
    tail.next = node;
    return node;
}
fn reverse(comptime T: type, start: *std.SinglyLinkedList(T)) *std.SinglyLinkedList(T) {
    if (start.first == null) return start;
    var it = start.first.?;
    var index: u32 = 1;
    while (it.next) |node| : (it = node.next.?) {
        index += 1;
    }
    _ = reverse_internal(T, start.first);
    start.first.?.next = null;
    start.first = it;
    return start;
}

test "reverse a 3 element list" {
    const L = std.SinglyLinkedList(u8);
    var list = L{};
    var node1 = L.Node{ .data = 1 };
    var node2 = L.Node{ .data = 2 };
    var node3 = L.Node{ .data = 3 };
    node1.next = &node2;
    node2.next = &node3;
    list.first = &node1;

    try std.testing.expectEqual(list.len(), 3);
    const reply = reverse(u8, &list);
    try std.testing.expectEqual(reply.len(), 3);
    var it = reply.first;
    var counter: u8 = 3;
    while (it) |node| : (it = node.next) {
        try std.testing.expectEqual(node.data, counter);
        counter -= 1;
    }
}
