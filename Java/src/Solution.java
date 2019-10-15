import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Solution {
    private static FileSystem fileSystem = new FileSystem();

    public static void main(String[] args) {
        List<Integer> vec1 = new ArrayList<>(Arrays.asList(1, 2));
        List<Integer> vec2 = new ArrayList<>(Arrays.asList(3));
        List<List<Integer>> vec2d = Arrays.asList(vec1, vec2);

        Vector2D vector2D = new Vector2D(vec2d);
        System.out.println(vector2D.hasNext());
        System.out.println(vector2D.next());
        vector2D.remove();
        System.out.println(vector2D.hasNext());
        System.out.println(vector2D.next());
        System.out.println(vector2D.hasNext());
        System.out.println(vector2D.next());
        System.out.println(vector2D.hasNext());
        System.out.println(vector2D.hasNext());
    }
}
