const std = @import("std");
fn sort(array: []u32) void {
    if (array.len < 2) return;
    if (array.len == 2) sort2(array);
}
fn sort2(array: [2]u32) void {
    if (array[0] < array[1]) return;
    std.mem.swap(u32, array[0], array[1]);
}
fn insertion_sort(array: []u32) void {
    const n = array.len;
    if (n == 0) return;
    var i: usize = 1;
    while (i < n) : (i += 1) {
        var j = i;
        const tmp = array[j];
        while (j > 0 and array[j - 1] > tmp) : (j -= 1) {
            array[j] = array[j - 1];
        }
        array[j] = tmp;
    }
}
fn selection_sort(array: []u32) void {
    const n = array.len;
    var i: usize = 0;
    if (n == 0) return;
    while (i < n - 1) : (i += 1) {
        var j: usize = i + 1;
        var min_idx = i;
        while (j < n) : (j += 1) {
            min_idx = if (@min(array[min_idx], array[j]) != array[min_idx]) j else min_idx;
        }
        std.mem.swap(u32, &array[min_idx], &array[i]);
    }
}
fn shell_sort(array: []u32) void {
    const n = array.len;
    if (n == 0) return;
    var h: usize = 1;
    while (h < n / 3) : (h = 3 * h + 1) {}
    while (h >= 1) : (h /= 3) {
        var i: usize = h;
        while (i < n) : (i += h) {
            var j = i;
            while (j >= h and array[j - h] > array[j]) : (j -= h) {
                std.mem.swap(u32, &array[j], &array[j - h]);
            }
        }
    }
}
fn merge_sort(array: []u32, left: usize, right: usize) void {
    if (left >= right) return;
    const mid = (left + right) >> 1;
    merge_sort(array, left, mid);
    merge_sort(array, mid + 1, right);
    in_place_merge(array, left, mid, right);
}
fn quick_sort(array: []u32) void {
    _ = array;
}
fn in_place_merge(array: []u32, left: usize, mid: usize, right: usize) void {
    var i = left;
    const j = mid + 1;
    while (i < mid + 1) {
        if (array[i] <= array[j]) {
            i += 1;
            continue;
        }
        const tmp = array[i];
        array[i] = array[j];
        // Binary search to insert tmp into array[j+1..]
        const S = struct {
            fn lower_u32(context: void, lhs: u32, rhs: u32) bool {
                _ = context;
                return lhs < rhs;
            }
        };
        const insert_pos = std.sort.upperBound(u32, tmp, array[j + 1 .. right + 1], {}, S.lower_u32);
        // if (insert_pos == array[j + 1 ..].len) {
        //     std.debug.print("LowerBound reached end of array. Val: {}\n", .{tmp});
        //     // insert_pos = array.len - 1;
        // }
        var k = j;
        while (k < j + insert_pos) : (k += 1) {
            array[k] = array[k + 1];
        }
        array[k] = tmp;
        // Binary search done
        i += 1;
    }
}

test "sort trivial array" {
    var trivial_array = [_]u32{};
    selection_sort(&trivial_array);
    try std.testing.expect(trivial_array.len == 0);

    trivial_array = [_]u32{};
    insertion_sort(&trivial_array);
    try std.testing.expect(trivial_array.len == 0);

    trivial_array = [_]u32{};
    shell_sort(&trivial_array);
    try std.testing.expect(trivial_array.len == 0);

    trivial_array = [_]u32{};
    merge_sort(&trivial_array, 0, 0);
    try std.testing.expect(trivial_array.len == 0);
}

test "two element array" {
    var array = [_]u32{ 2, 0 };
    selection_sort(&array);
    try std.testing.expectEqualSlices(u32, &[_]u32{ 0, 2 }, &array);

    array = [_]u32{ 2, 0 };
    insertion_sort(&array);
    try std.testing.expectEqualSlices(u32, &[_]u32{ 0, 2 }, &array);

    array = [_]u32{ 2, 0 };
    shell_sort(&array);
    try std.testing.expectEqualSlices(u32, &[_]u32{ 0, 2 }, &array);

    array = [_]u32{ 2, 0 };
    merge_sort(&array, 0, 1);
    try std.testing.expectEqualSlices(u32, &[_]u32{ 0, 2 }, &array);
}

test "three element array" {
    var array = [_]u32{ 90, 32, 29 };
    selection_sort(&array);
    try std.testing.expectEqualSlices(u32, &[_]u32{ 29, 32, 90 }, &array);

    array = [_]u32{ 90, 32, 29 };
    insertion_sort(&array);
    try std.testing.expectEqualSlices(u32, &[_]u32{ 29, 32, 90 }, &array);

    array = [_]u32{ 90, 32, 29 };
    shell_sort(&array);
    try std.testing.expectEqualSlices(u32, &[_]u32{ 29, 32, 90 }, &array);

    array = [_]u32{ 90, 32, 29 };
    merge_sort(&array, 0, 2);
    try std.testing.expectEqualSlices(u32, &[_]u32{ 29, 32, 90 }, &array);
}

test "five element array" {
    var array = [_]u32{ 90, 32, 2, 19, 29 };
    selection_sort(&array);
    try std.testing.expectEqualSlices(u32, &[_]u32{ 2, 19, 29, 32, 90 }, &array);

    array = [_]u32{ 90, 32, 2, 19, 29 };
    insertion_sort(&array);
    try std.testing.expectEqualSlices(u32, &[_]u32{ 2, 19, 29, 32, 90 }, &array);

    array = [_]u32{ 90, 32, 2, 19, 29 };
    shell_sort(&array);
    try std.testing.expectEqualSlices(u32, &[_]u32{ 2, 19, 29, 32, 90 }, &array);

    array = [_]u32{ 90, 32, 2, 19, 29 };
    merge_sort(&array, 0, array.len - 1);
    try std.testing.expectEqualSlices(u32, &[_]u32{ 2, 19, 29, 32, 90 }, &array);
}

test "duplicates in array" {
    var array = [_]u32{ 1, 1, 2, 2, 2, 3, 1, 1, 0 };
    selection_sort(&array);
    try std.testing.expectEqualSlices(u32, &[_]u32{ 0, 1, 1, 1, 1, 2, 2, 2, 3 }, &array);

    array = [_]u32{ 1, 1, 2, 2, 2, 3, 1, 1, 0 };
    insertion_sort(&array);
    try std.testing.expectEqualSlices(u32, &[_]u32{ 0, 1, 1, 1, 1, 2, 2, 2, 3 }, &array);

    array = [_]u32{ 1, 1, 2, 2, 2, 3, 1, 1, 0 };
    shell_sort(&array);
    try std.testing.expectEqualSlices(u32, &[_]u32{ 0, 1, 1, 1, 1, 2, 2, 2, 3 }, &array);

    array = [_]u32{ 1, 1, 2, 2, 2, 3, 1, 1, 0 };
    merge_sort(&array, 0, array.len - 1);
    try std.testing.expectEqualSlices(u32, &[_]u32{ 0, 1, 1, 1, 1, 2, 2, 2, 3 }, &array);
}
// Can't really test stability using just U32 values
// test "stability" {
//     var array = [_]u32{ 1, 1, 2, 2, 2, 3, 1, 1};
//     const first_one_ptr = &array[0];
//     selection_sort(&array);
//     try std.testing.expectEqual(array[first_one_ptr], )
//     try std.testing.expectEqualSlices(u32, &[_]u32{ 0, 1, 1, 1, 1, 2, 2, 2, 3 }, &array);
// }
