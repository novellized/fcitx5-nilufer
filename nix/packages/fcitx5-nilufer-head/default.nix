{
  callPackage,
  inputs,
}:
(callPackage ../fcitx5-nilufer { }).overrideAttrs (old: {
  pname = "fcitx5-nilufer-head";
  version = "0-unstable";
  src = inputs.self;
})
