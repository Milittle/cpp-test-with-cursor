// 创建 clang-tidy 检查器
class ComparisonOperatorChecker : public clang::tidy::ClangTidyCheck {
public:
  void registerMatchers(clang::ast::MatchFinder *Finder) override {
    // 匹配比较函数
    Finder->addMatcher(
      functionDecl(hasAnyParameter(hasType(isConstReferenceType()))).bind("compareFunc"),
      this);
  }
}; 