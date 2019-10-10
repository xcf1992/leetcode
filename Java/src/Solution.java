public class Solution {
    private static FileSystem fileSystem = new FileSystem();

    public static void main(String[] args) {
        boolean result = fileSystem.createPath("/a/b", 1);
        System.out.println(result);
    }
}
