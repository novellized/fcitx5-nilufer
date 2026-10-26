{
  config,
  lib,
  inputs,
  pkgs,
  ...
}:
with lib;
let
  cfg = config.services.fcitx5-nilufer;
  fcitx5-nilufer = inputs.self.packages.${pkgs.stdenv.hostPlatform.system}.fcitx5-nilufer;

  legacyUsers = optional (cfg.user != null && cfg.user != "") cfg.user;
  effectiveUsers = unique (legacyUsers ++ cfg.users);

  syntacticallyInvalidUsers = filter (
    user: user == "" || (builtins.match "[A-Za-z_][A-Za-z0-9_-]*" user) == null
  ) effectiveUsers;

  unknownUsers = filter (user: !(builtins.hasAttr user config.users.users)) effectiveUsers;
in
{
  options.services.fcitx5-nilufer = {
    enable = mkEnableOption "Fcitx5 Nilüfer integration";

    package = mkOption {
      type = types.package;
      default = fcitx5-nilufer;
      defaultText = literalExpression "inputs.self.packages.\${pkgs.stdenv.hostPlatform.system}.fcitx5-nilufer";
      description = "The fcitx5-nilufer package to install.";
    };

    # Backward compatible with the old module API, but no longer defaults to "".
    user = mkOption {
      type = types.nullOr types.str;
      default = null;
      example = "alice";
      description = ''
        Backward-compatible single user to start the Nilüfer server for.

        Prefer `services.fcitx5-nilufer.users` for new configurations.
      '';
    };

    users = mkOption {
      type = types.listOf types.str;
      default = [ ];
      example = [
        "alice"
        "bob"
      ];
      description = ''
        Linux users to start system-level fcitx5-nilufer-server instances for.

        Each configured user gets one fcitx5-nilufer-server@<user>.service instance.
      '';
    };
  };

  config = mkIf cfg.enable {
    assertions = [
      {
        assertion = cfg.user != "";
        message = "services.fcitx5-nilufer.user must not be an empty string; use null or services.fcitx5-nilufer.users.";
      }
      {
        assertion = effectiveUsers != [ ];
        message = "services.fcitx5-nilufer requires at least one user. Set services.fcitx5-nilufer.users = [ \"alice\" ];";
      }
      {
        assertion = syntacticallyInvalidUsers == [ ];
        message = "services.fcitx5-nilufer.users/user contains invalid Linux usernames.";
      }
      {
        assertion = unknownUsers == [ ];
        message = "services.fcitx5-nilufer.users/user must contain users declared in users.users.";
      }
    ];

    i18n.inputMethod.fcitx5.addons = [ cfg.package ];

    users.users.uinput_proxy = {
      isSystemUser = true;
      group = "input";
    };

    services.udev.packages = [ cfg.package ];
    systemd.packages = [ cfg.package ];

    systemd.targets.multi-user.wants = map (user: "fcitx5-nilufer-server@${user}.service") effectiveUsers;
  };
}
