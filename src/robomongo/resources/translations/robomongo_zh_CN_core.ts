<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="zh_CN">
<context>
    <name>Robomongo::ConnectionBasicTab</name>
    <message>
        <source>Type:</source>
        <translation>类型:</translation>
    </message>
    <message>
        <source>Name:</source>
        <translation>名称:</translation>
    </message>
    <message>
        <source>Choose any connection name that will help you to identify this connection.</source>
        <translation>选择任何有助于您识别此连接的名称。</translation>
    </message>
    <message>
        <source>Address:</source>
        <translation>地址:</translation>
    </message>
    <message>
        <source>Specify host and port of MongoDB server. Host can be either IPv4, IPv6 or domain name.</source>
        <translation>指定 MongoDB 服务器的主机和端口。主机可以是 IPv4、IPv6 或域名。</translation>
    </message>
    <message>
        <source>Members:</source>
        <translation>成员:</translation>
    </message>
    <message>
        <source>Set Name:</source>
        <translation>集合名称:</translation>
    </message>
    <message>
        <source>Import connection details from MongoDB URI connection string</source>
        <translation>从 MongoDB URI 连接字符串导入连接详情</translation>
    </message>
    <message>
        <source>From URI</source>
        <translation>从 URI</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>错误</translation>
    </message>
    <message>
        <source>Replica set members cannot be empty. Please enter at least one member.</source>
        <translation>副本集成员不能为空。请输入至少一个成员。</translation>
    </message>
    <message>
        <source>Replica set member items must all contain &apos;:&apos; between hostname and port.</source>
        <translation>副本集成员项在主机名和端口之间必须包含 &apos;:&apos;。</translation>
    </message>
    <message>
        <source>Please remove duplicate member, two replica set members cannot have the same hostname and port.</source>
        <translation>请移除重复成员，两个副本集成员不能具有相同的主机名和端口。</translation>
    </message>
    <message>
        <source>New Connection</source>
        <translation>新建连接</translation>
    </message>
    <message>
        <source>MongoDB URI:
</source>
        <translation>MongoDB URI:
</translation>
    </message>
</context>
<context>
    <name>Robomongo::ConnectionAuthTab</name>
    <message>
        <source>Perform authentication</source>
        <translation>执行认证</translation>
    </message>
    <message>
        <source>&lt;nobr&gt;The admin database is unique in MongoDB.&lt;/nobr&gt; Users with normal access to the admin database have read and write access to &lt;b&gt;all databases&lt;/b&gt;.</source>
        <translation>&lt;nobr&gt;admin 数据库在 MongoDB 中是唯一的。&lt;/nobr&gt; 拥有 admin 数据库正常访问权限的用户对 &lt;b&gt;所有数据库&lt;/b&gt; 具有读写权限。</translation>
    </message>
    <message>
        <source>User Name</source>
        <translation>用户名</translation>
    </message>
    <message>
        <source>Auth Mechanism</source>
        <translation>认证机制</translation>
    </message>
    <message>
        <source>Password</source>
        <translation>密码</translation>
    </message>
    <message>
        <source>Database</source>
        <translation>数据库</translation>
    </message>
    <message>
        <source>Comma-separated e.g. products, users</source>
        <translation>以逗号分隔，例如 products, users</translation>
    </message>
    <message>
        <source>Databases</source>
        <translation>数据库</translation>
    </message>
    <message>
        <source>Some MongoDB users might not have the permission to get the list of database names (&lt;b&gt;listDatabases&lt;/b&gt; command). For this case, manually add the name of the database(s) that this user has access to.</source>
        <translation>某些 MongoDB 用户可能没有获取数据库名称列表（&lt;b&gt;listDatabases&lt;/b&gt; 命令）的权限。在这种情况下，请手动添加该用户有权访问的数据库名称。</translation>
    </message>
    <message>
        <source>Manually specify visible databases</source>
        <translation>手动指定可见的数据库</translation>
    </message>
</context>
<context>
    <name>Robomongo::SshTunnelTab</name>
    <message>
        <source>Use SSH tunnel</source>
        <translation>使用 SSH 隧道</translation>
    </message>
    <message>
        <source>SSH Address:</source>
        <translation>SSH 地址:</translation>
    </message>
    <message>
        <source>SSH User Name:</source>
        <translation>SSH 用户名:</translation>
    </message>
    <message>
        <source>SSH Auth Method:</source>
        <translation>SSH 认证方式:</translation>
    </message>
    <message>
        <source>User Password:</source>
        <translation>用户密码:</translation>
    </message>
    <message>
        <source>Private key:</source>
        <translation>私钥:</translation>
    </message>
    <message>
        <source>Passphrase:</source>
        <translation>密码短语:</translation>
    </message>
    <message>
        <source>Password</source>
        <translation>密码</translation>
    </message>
    <message>
        <source>Private Key</source>
        <translation>私钥</translation>
    </message>
    <message>
        <source>DSA, RSA, and on Windows/macOS ECDSA, Ed25519 keys are supported. PPK keys must be converted to OPENSSH format.</source>
        <translation>支持 DSA, RSA, 以及在 Windows/macOS 上的 ECDSA, Ed25519 密钥。PPK 密钥必须转换为 OPENSSH 格式。</translation>
    </message>
    <message>
        <source>SSH is currently not supported for Replica Set connections</source>
        <translation>目前副本集连接不支持 SSH</translation>
    </message>
    <message>
        <source>Select private key file</source>
        <translation>选择私钥文件</translation>
    </message>
    <message>
        <source>Settings are incomplete</source>
        <translation>设置不完整</translation>
    </message>
    <message>
        <source>Private key file &quot;%1&quot; doesn&apos;t exist</source>
        <translation>私钥文件 &quot;%1&quot; 不存在</translation>
    </message>
</context>
<context>
    <name>Robomongo::SSLTab</name>
    <message>
        <source>Use TLS protocol</source>
        <translation>使用 TLS 协议</translation>
    </message>
    <message>
        <source>Authentication Method: </source>
        <translation>认证方法: </translation>
    </message>
    <message>
        <source>Self-signed Certificate</source>
        <translation>自签名证书</translation>
    </message>
    <message>
        <source>Use CA Certificate</source>
        <translation>使用 CA 证书</translation>
    </message>
    <message>
        <source>In general, avoid using self-signed certificates unless the network is trusted. If self-signed certificate is used, the communications channel will be encrypted however there will be no validation of server identity.</source>
        <translation>通常情况下，除非网络是受信任的，否则请避免使用自签名证书。如果使用自签名证书，通信通道将被加密，但不会验证服务器身份。</translation>
    </message>
    <message>
        <source>CA Certificate:</source>
        <translation>CA 证书:</translation>
    </message>
    <message>
        <source>Use PEM Cert./Key: </source>
        <translation>使用 PEM 证书/密钥: </translation>
    </message>
    <message>
        <source>Enable this option to connect to a MongoDB that requires CA-signed client certificates/key file.</source>
        <translation>启用此选项以连接到需要 CA 签名客户端证书/密钥文件的 MongoDB。</translation>
    </message>
    <message>
        <source>PEM Certificate/Key: </source>
        <translation>PEM 证书/密钥: </translation>
    </message>
    <message>
        <source>Passphrase: </source>
        <translation>密码短语: </translation>
    </message>
    <message>
        <source>Ask for passphrase each time</source>
        <translation>每次询问密码短语</translation>
    </message>
    <message>
        <source>Advanced Options</source>
        <translation>高级选项</translation>
    </message>
    <message>
        <source>CRL (Revocation List): </source>
        <translation>CRL (撤销列表): </translation>
    </message>
    <message>
        <source>Invalid Hostnames: </source>
        <translation>无效主机名: </translation>
    </message>
    <message>
        <source>Not Allowed</source>
        <translation>不允许</translation>
    </message>
    <message>
        <source>Allowed</source>
        <translation>允许</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>错误</translation>
    </message>
    <message>
        <source>Error: </source>
        <translation>错误: </translation>
    </message>
    <message>
        <source> file does not exist</source>
        <translation> 文件不存在</translation>
    </message>
    <message>
        <source>CA-signed certificate</source>
        <translation>CA 签名证书</translation>
    </message>
    <message>
        <source>PEM Certificate/Key</source>
        <translation>PEM 证书/密钥</translation>
    </message>
    <message>
        <source>CRL (Revocation List)</source>
        <translation>CRL (撤销列表)</translation>
    </message>
</context>
<context>
    <name>Robomongo::ConnectionAdvancedTab</name>
    <message>
        <source>Default Database:</source>
        <translation>默认数据库:</translation>
    </message>
    <message>
        <source>Database, that will be default (&lt;code&gt;db&lt;/code&gt; shell variable will point to this database). By default, default database will be the one you authenticate on, or &lt;code&gt;test&lt;/code&gt; otherwise. Leave this field empty, if you want default behavior.</source>
        <translation>将作为默认数据库（&lt;code&gt;db&lt;/code&gt; Shell 变量将指向此数据库）。默认情况下，默认数据库将是您进行身份验证的数据库，否则为 &lt;code&gt;test&lt;/code&gt;。如果您希望使用默认行为，请将此字段留空。</translation>
    </message>
</context>
<context>
    <name>Robomongo::SSLTab</name>
    <message>
        <source> mongo --tlsCAFile : Certificate Authority file for TLS</source>
        <translation> mongo --tlsCAFile : 用于 TLS 的证书颁发机构 (CA) 文件</translation>
    </message>
    <message>
        <source> mongo --tlsCertificateKeyFile : PEM certificate/key file for TLS</source>
        <translation> mongo --tlsCertificateKeyFile : 用于 TLS 的 PEM 证书/密钥文件</translation>
    </message>
    <message>
        <source> mongo --tlsCertificateKeyFilePassword : Password for key in PEM file for TLS</source>
        <translation> mongo --tlsCertificateKeyFilePassword : 用于 TLS 的 PEM 文件中的密钥密码</translation>
    </message>
    <message>
        <source> mongo --tlsAllowInvalidHostnames : Allow connections to servers with non-matching hostnames</source>
        <translation> mongo --tlsAllowInvalidHostnames : 允许连接到主机名不匹配的服务器</translation>
    </message>
    <message>
        <source> mongo --tlsAllowInvalidCertificates : Allow connections to servers with invalid certificates</source>
        <translation> mongo --tlsAllowInvalidCertificates : 允许连接到证书无效的服务器</translation>
    </message>
    <message>
        <source> mongo --tlsCRLFile : Certificate Revocation List file for TLS</source>
        <translation> mongo --tlsCRLFile : 用于 TLS 的证书撤销列表 (CRL) 文件</translation>
    </message>
    <message>
        <source>Use TLS protocol</source>
        <translation>使用 TLS 协议</translation>
    </message>
    <message>
        <source>Authentication Method: </source>
        <translation>认证方法: </translation>
    </message>
    <message>
        <source>Self-signed Certificate</source>
        <translation>自签名证书</translation>
    </message>
    <message>
        <source>Use CA Certificate</source>
        <translation>使用 CA 证书</translation>
    </message>
    <message>
        <source>In general, avoid using self-signed certificates unless the network is trusted. If self-signed certificate is used, the communications channel will be encrypted however there will be no validation of server identity.</source>
        <translation>通常情况下，除非网络是受信任的，否则请避免使用自签名证书。如果使用自签名证书，通信通道将被加密，但不会验证服务器身份。</translation>
    </message>
    <message>
        <source>CA Certificate:</source>
        <translation>CA 证书:</translation>
    </message>
    <message>
        <source>Use PEM Cert./Key: </source>
        <translation>使用 PEM 证书/密钥: </translation>
    </message>
    <message>
        <source>Enable this option to connect to a MongoDB that requires CA-signed client certificates/key file.</source>
        <translation>启用此选项以连接到需要 CA 签名客户端证书/密钥文件的 MongoDB。</translation>
    </message>
    <message>
        <source>PEM Certificate/Key: </source>
        <translation>PEM 证书/密钥: </translation>
    </message>
    <message>
        <source>Passphrase: </source>
        <translation>密码短语: </translation>
    </message>
    <message>
        <source>Ask for passphrase each time</source>
        <translation>每次询问密码短语</translation>
    </message>
    <message>
        <source>Advanced Options</source>
        <translation>高级选项</translation>
    </message>
    <message>
        <source>CRL (Revocation List): </source>
        <translation>CRL (撤销列表): </translation>
    </message>
    <message>
        <source>Invalid Hostnames: </source>
        <translation>无效主机名: </translation>
    </message>
    <message>
        <source>Not Allowed</source>
        <translation>不允许</translation>
    </message>
    <message>
        <source>Allowed</source>
        <translation>允许</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>错误</translation>
    </message>
    <message>
        <source>Error: </source>
        <translation>错误: </translation>
    </message>
    <message>
        <source> file does not exist</source>
        <translation> 文件不存在</translation>
    </message>
    <message>
        <source>CA-signed certificate</source>
        <translation>CA 签名证书</translation>
    </message>
    <message>
        <source>PEM Certificate/Key</source>
        <translation>PEM 证书/密钥</translation>
    </message>
    <message>
        <source>CRL (Revocation List)</source>
        <translation>CRL (撤销列表)</translation>
    </message>
    <message>
        <source>Choose File</source>
        <translation>选择文件</translation>
    </message>
</context>
<context>
    <name>Robomongo::ConnectionBasicTab</name>
    <message>
        <source>Type:</source>
        <translation>类型:</translation>
    </message>
    <message>
        <source>Direct Connection</source>
        <translation>直接连接</translation>
    </message>
    <message>
        <source>Replica Set</source>
        <translation>副本集</translation>
    </message>
    <message>
        <source>Name:</source>
        <translation>名称:</translation>
    </message>
    <message>
        <source>Choose any connection name that will help you to identify this connection.</source>
        <translation>选择任何有助于您识别此连接的名称。</translation>
    </message>
    <message>
        <source>Address:</source>
        <translation>地址:</translation>
    </message>
    <message>
        <source>Specify host and port of MongoDB server. Host can be either IPv4, IPv6 or domain name.</source>
        <translation>指定 MongoDB 服务器的主机和端口。主机可以是 IPv4、IPv6 或域名。</translation>
    </message>
    <message>
        <source>Members:</source>
        <translation>成员:</translation>
    </message>
    <message>
        <source>Set Name:</source>
        <translation>集合名称:</translation>
    </message>
    <message>
        <source>Import connection details from MongoDB URI connection string</source>
        <translation>从 MongoDB URI 连接字符串导入连接详情</translation>
    </message>
    <message>
        <source>From URI</source>
        <translation>从 URI</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>错误</translation>
    </message>
    <message>
        <source>Replica set members cannot be empty. Please enter at least one member.</source>
        <translation>副本集成员不能为空。请输入至少一个成员。</translation>
    </message>
    <message>
        <source>Replica set member items must all contain &apos;:&apos; between hostname and port.</source>
        <translation>副本集成员项在主机名和端口之间必须包含 &apos;:&apos;。</translation>
    </message>
    <message>
        <source>Please remove duplicate member, two replica set members cannot have the same hostname and port.</source>
        <translation>请移除重复成员，两个副本集成员不能具有相同的主机名和端口。</translation>
    </message>
    <message>
        <source>New Connection</source>
        <translation>新建连接</translation>
    </message>
</context>
<context>
    <name>Robomongo::ConnectionAuthTab</name>
    <message>
        <source>Perform authentication</source>
        <translation>执行认证</translation>
    </message>
    <message>
        <source>&lt;nobr&gt;The admin database is unique in MongoDB.&lt;/nobr&gt; Users with normal access to the admin database have read and write access to &lt;b&gt;all databases&lt;/b&gt;.</source>
        <translation>&lt;nobr&gt;admin 数据库在 MongoDB 中是唯一的。&lt;/nobr&gt; 拥有 admin 数据库正常访问权限的用户对 &lt;b&gt;所有数据库&lt;/b&gt; 具有读写权限。</translation>
    </message>
    <message>
        <source>User Name</source>
        <translation>用户名</translation>
    </message>
    <message>
        <source>Auth Mechanism</source>
        <translation>认证机制</translation>
    </message>
    <message>
        <source>Password</source>
        <translation>密码</translation>
    </message>
    <message>
        <source>Database</source>
        <translation>数据库</translation>
    </message>
    <message>
        <source>Comma-separated e.g. products, users</source>
        <translation>以逗号分隔，例如 products, users</translation>
    </message>
    <message>
        <source>Databases</source>
        <translation>数据库</translation>
    </message>
    <message>
        <source>Some MongoDB users might not have the permission to get the list of database names (&lt;b&gt;listDatabases&lt;/b&gt; command). For this case, manually add the name of the database(s) that this user has access to.</source>
        <translation>某些 MongoDB 用户可能没有获取数据库名称列表（&lt;b&gt;listDatabases&lt;/b&gt; 命令）的权限。在这种情况下，请手动添加该用户有权访问的数据库名称。</translation>
    </message>
    <message>
        <source>Manually specify visible databases</source>
        <translation>手动指定可见的数据库</translation>
    </message>
</context>
<context>
    <name>Robomongo::SshTunnelTab</name>
    <message>
        <source>Use SSH tunnel</source>
        <translation>使用 SSH 隧道</translation>
    </message>
    <message>
        <source>Ask for password each time</source>
        <translation>每次询问密码</translation>
    </message>
    <message>
        <source>Ask for passphrase each time</source>
        <translation>每次询问密码短语</translation>
    </message>
    <message>
        <source>Password</source>
        <translation>密码</translation>
    </message>
    <message>
        <source>Private Key</source>
        <translation>私钥</translation>
    </message>
    <message>
        <source>User Password:</source>
        <translation>用户密码:</translation>
    </message>
    <message>
        <source>Private key:</source>
        <translation>私钥:</translation>
    </message>
    <message>
        <source>Passphrase:</source>
        <translation>密码短语:</translation>
    </message>
    <message>
        <source>SSH Address:</source>
        <translation>SSH 地址:</translation>
    </message>
    <message>
        <source>SSH User Name:</source>
        <translation>SSH 用户名:</translation>
    </message>
    <message>
        <source>SSH Auth Method:</source>
        <translation>SSH 认证方式:</translation>
    </message>
    <message>
        <source>Select private key file</source>
        <translation>选择私钥文件</translation>
    </message>
    <message>
        <source>Private key files (*)</source>
        <translation>私钥文件 (*)</translation>
    </message>
    <message>
        <source>Settings are incomplete</source>
        <translation>设置不完整</translation>
    </message>
    <message>
        <source>SSH is currently not supported for Replica Set connections</source>
        <translation>目前副本集连接不支持 SSH</translation>
    </message>
    <message>
        <source>Private key file &quot;%1&quot; doesn&apos;t exist</source>
        <translation>私钥文件 &quot;%1&quot; 不存在</translation>
    </message>
</context>
<context>
    <name>Robomongo::SSLTab</name>
    <message>
        <source>Use TLS protocol</source>
        <translation>使用 TLS 协议</translation>
    </message>
    <message>
        <source>Authentication Method: </source>
        <translation>认证方法: </translation>
    </message>
    <message>
        <source>Self-signed Certificate</source>
        <translation>自签名证书</translation>
    </message>
    <message>
        <source>Use CA Certificate</source>
        <translation>使用 CA 证书</translation>
    </message>
    <message>
        <source>In general, avoid using self-signed certificates unless the network is trusted. If self-signed certificate is used, the communications channel will be encrypted however there will be no validation of server identity.</source>
        <translation>通常情况下，除非网络是受信任的，否则请避免使用自签名证书。如果使用自签名证书，通信通道将被加密，但不会验证服务器身份。</translation>
    </message>
    <message>
        <source>CA Certificate:</source>
        <translation>CA 证书:</translation>
    </message>
    <message>
        <source>Use PEM Cert./Key: </source>
        <translation>使用 PEM 证书/密钥: </translation>
    </message>
    <message>
        <source>PEM Certificate/Key: </source>
        <translation>PEM 证书/密钥: </translation>
    </message>
    <message>
        <source>Advanced Options</source>
        <translation>高级选项</translation>
    </message>
    <message>
        <source>CRL (Revocation List): </source>
        <translation>CRL (撤销列表): </translation>
    </message>
    <message>
        <source>Invalid Hostnames: </source>
        <translation>无效主机名: </translation>
    </message>
    <message>
        <source>Not Allowed</source>
        <translation>不允许</translation>
    </message>
    <message>
        <source>Allowed</source>
        <translation>允许</translation>
    </message>
    <message>
        <source>Choose File</source>
        <translation>选择文件</translation>
    </message>
</context>
<context>
    <name>Robomongo::ConnectionAdvancedTab</name>
    <message>
        <source>Database, that will be default (&lt;code&gt;db&lt;/code&gt; shell variable will point to this database). By default, default database will be the one you authenticate on, or &lt;code&gt;test&lt;/code&gt; otherwise. Leave this field empty, if you want default behavior.</source>
        <translation>将作为默认数据库（&lt;code&gt;db&lt;/code&gt; Shell 变量将指向此数据库）。默认情况下，默认数据库将是您进行身份验证的数据库，否则为 &lt;code&gt;test&lt;/code&gt;。如果您希望使用默认行为，请将此字段留空。</translation>
    </message>
    <message>
        <source>Default Database:</source>
        <translation>默认数据库:</translation>
    </message>
</context>
<context>
    <name>Robomongo::ConnectionAuthTab</name>
    <message>
        <source>Perform authentication</source>
        <translation>执行认证</translation>
    </message>
    <message>
        <source>&lt;nobr&gt;The admin database is unique in MongoDB.&lt;/nobr&gt; Users with normal access to the admin database have read and write access to &lt;b&gt;all databases&lt;/b&gt;.</source>
        <translation>&lt;nobr&gt;admin 数据库在 MongoDB 中是唯一的。&lt;/nobr&gt; 拥有 admin 数据库正常访问权限的用户对 &lt;b&gt;所有数据库&lt;/b&gt; 具有读写权限。</translation>
    </message>
    <message>
        <source>User Name</source>
        <translation>用户名</translation>
    </message>
    <message>
        <source>Auth Mechanism</source>
        <translation>认证机制</translation>
    </message>
    <message>
        <source>Password</source>
        <translation>密码</translation>
    </message>
    <message>
        <source>Database</source>
        <translation>数据库</translation>
    </message>
    <message>
        <source>Comma-separated e.g. products, users</source>
        <translation>以逗号分隔，例如 products, users</translation>
    </message>
    <message>
        <source>Databases</source>
        <translation>数据库</translation>
    </message>
    <message>
        <source>Some MongoDB users might not have the permission to get the list of database names (&lt;b&gt;listDatabases&lt;/b&gt; command). For this case, manually add the name of the database(s) that this user has access to.</source>
        <translation>某些 MongoDB 用户可能没有获取数据库名称列表（&lt;b&gt;listDatabases&lt;/b&gt; 命令）的权限。在这种情况下，请手动添加该用户有权访问的数据库名称。</translation>
    </message>
    <message>
        <source>Manually specify visible databases</source>
        <translation>手动指定可见的数据库</translation>
    </message>
</context>
<context>
    <name>Robomongo::ConnectionSettings</name>
    <message>
        <source>New Connection</source>
        <translation>新建连接</translation>
    </message>
</context>
<context>
    <name>Robomongo::ConnectionBasicTab</name>
    <message>
        <source>Type:</source>
        <translation>类型:</translation>
    </message>
    <message>
        <source>Direct Connection</source>
        <translation>直接连接</translation>
    </message>
    <message>
        <source>Replica Set</source>
        <translation>副本集</translation>
    </message>
    <message>
        <source>Name:</source>
        <translation>名称:</translation>
    </message>
    <message>
        <source>Choose any connection name that will help you to identify this connection.</source>
        <translation>选择任何有助于您识别此连接的名称。</translation>
    </message>
    <message>
        <source>Address:</source>
        <translation>地址:</translation>
    </message>
    <message>
        <source>Specify host and port of MongoDB server. Host can be either IPv4, IPv6 or domain name.</source>
        <translation>指定 MongoDB 服务器的主机和端口。主机可以是 IPv4、IPv6 或域名。</translation>
    </message>
    <message>
        <source>Members:</source>
        <translation>成员:</translation>
    </message>
    <message>
        <source>Set Name:</source>
        <translation>集合名称:</translation>
    </message>
    <message>
        <source>Import connection details from MongoDB URI connection string</source>
        <translation>从 MongoDB URI 连接字符串导入连接详情</translation>
    </message>
    <message>
        <source>From URI</source>
        <translation>从 URI</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>错误</translation>
    </message>
    <message>
        <source>Replica set members cannot be empty. Please enter at least one member.</source>
        <translation>副本集成员不能为空。请输入至少一个成员。</translation>
    </message>
    <message>
        <source>Replica set member items must all contain ':' between hostname and port.</source>
        <translation>副本集成员项在主机名和端口之间必须包含 ':'。</translation>
    </message>
    <message>
        <source>Please remove duplicate member, two replica set members cannot have the same hostname and port.</source>
        <translation>请移除重复成员，两个副本集成员不能具有相同的主机名和端口。</translation>
    </message>
    <message>
        <source>New Connection</source>
        <translation>新建连接</translation>
    </message>
    <message>
        <source>MongoDB URI:
</source>
        <translation>MongoDB URI:
</translation>
    </message>
</context>
<context>
    <name>Robomongo::MongoServer</name>
    <message>
        <source>document.</source>
        <translation>文档。</translation>
    </message>
    <message>
        <source>documents.</source>
        <translation>文档。</translation>
    </message>
    <message>
        <source>all documents.</source>
        <translation>所有文档。</translation>
    </message>
    <message>
        <source>(logic error).</source>
        <translation>(逻辑错误)。</translation>
    </message>
    <message>
        <source>Failed to remove </source>
        <translation>移除失败 </translation>
    </message>
    <message>
        <source>Removed </source>
        <translation>已移除 </translation>
    </message>
    <message>
        <source>Cannot connect to replica set "%1"</source>
        <translation>无法连接到副本集 "%1"</translation>
    </message>
    <message>
        <source>. 
A primary with different host name [%1] found in server side. </source>
        <translation>。
在服务器端发现了一个具有不同主机名 [%1] 的主节点。</translation>
    </message>
    <message>
        <source>Please double check if same host names and ports are used as in server's replica set configuration. 
If same set name is used for different replica sets, this configuration is supported only on different instances of Robo 3T.  Please open a new Robo 3T instance for each replica set which has the same set name.

Reason:
</source>
        <translation>请仔细检查是否使用了与服务器副本集配置中相同的主机名和端口。
如果不同的副本集使用了相同的集合名称，则仅在 Robo 3T 的不同实例上支持此配置。请为每个具有相同集合名称的副本集打开一个新的 Robo 3T 实例。

原因:
</translation>
    </message>
    <message>
        <source>. 
Set's primary is unreachable.

Reason:
</source>
        <translation>。
集合的主节点无法访问。

原因:
</translation>
    </message>
    <message>
        <source>Cannot connect to the MongoDB at %1.

Error:
TLS connection failure: </source>
        <translation>无法连接到位于 %1 的 MongoDB。

错误:
TLS 连接失败: </translation>
    </message>
    <message>
        <source>Cannot connect to the MongoDB at %1.

Error:
</source>
        <translation>无法连接到位于 %1 的 MongoDB。

错误:
</translation>
    </message>
</context>
<context>
    <name>Robomongo::ConnectionAuthTab</name>
    <message>
        <source>Perform authentication</source>
        <translation>执行认证</translation>
    </message>
    <message>
        <source>&lt;nobr&gt;The admin database is unique in MongoDB.&lt;/nobr&gt; Users with normal access to the admin database have read and write access to &lt;b&gt;all databases&lt;/b&gt;.</source>
        <translation>&lt;nobr&gt;admin 数据库在 MongoDB 中是唯一的。&lt;/nobr&gt; 拥有 admin 数据库正常访问权限的用户对 &lt;b&gt;所有数据库&lt;/b&gt; 具有读写权限。</translation>
    </message>
    <message>
        <source>User Name</source>
        <translation>用户名</translation>
    </message>
    <message>
        <source>Auth Mechanism</source>
        <translation>认证机制</translation>
    </message>
    <message>
        <source>Password</source>
        <translation>密码</translation>
    </message>
    <message>
        <source>Database</source>
        <translation>数据库</translation>
    </message>
    <message>
        <source>Comma-separated e.g. products, users</source>
        <translation>以逗号分隔，例如 products, users</translation>
    </message>
    <message>
        <source>Databases</source>
        <translation>数据库</translation>
    </message>
    <message>
        <source>Some MongoDB users might not have the permission to get the list of database names (&lt;b&gt;listDatabases&lt;/b&gt; command). For this case, manually add the name of the database(s) that this user has access to.</source>
        <translation>某些 MongoDB 用户可能没有获取数据库名称列表（&lt;b&gt;listDatabases&lt;/b&gt; 命令）的权限。在这种情况下，请手动添加该用户有权访问的数据库名称。</translation>
    </message>
    <message>
        <source>Manually specify visible databases</source>
        <translation>手动指定可见的数据库</translation>
    </message>
</context>
<context>
    <name>Robomongo::SSLTab</name>
    <message>
        <source>Use TLS protocol</source>
        <translation>使用 TLS 协议</translation>
    </message>
    <message>
        <source>Authentication Method: </source>
        <translation>认证方法: </translation>
    </message>
    <message>
        <source>Self-signed Certificate</source>
        <translation>自签名证书</translation>
    </message>
    <message>
        <source>Use CA Certificate</source>
        <translation>使用 CA 证书</translation>
    </message>
    <message>
        <source>In general, avoid using self-signed certificates unless the network is trusted. If self-signed certificate is used, the communications channel will be encrypted however there will be no validation of server identity.</source>
        <translation>通常情况下，除非网络是受信任的，否则请避免使用自签名证书。如果使用自签名证书，通信通道将被加密，但不会验证服务器身份。</translation>
    </message>
    <message>
        <source>CA Certificate:</source>
        <translation>CA 证书:</translation>
    </message>
    <message>
        <source>Use PEM Cert./Key: </source>
        <translation>使用 PEM 证书/密钥: </translation>
    </message>
    <message>
        <source>Enable this option to connect to a MongoDB that requires CA-signed client certificates/key file.</source>
        <translation>启用此选项以连接到需要 CA 签名客户端证书/密钥文件的 MongoDB。</translation>
    </message>
    <message>
        <source>PEM Certificate/Key: </source>
        <translation>PEM 证书/密钥: </translation>
    </message>
    <message>
        <source>Passphrase: </source>
        <translation>密码短语: </translation>
    </message>
    <message>
        <source>Ask for passphrase each time</source>
        <translation>每次询问密码短语</translation>
    </message>
    <message>
        <source>Advanced Options</source>
        <translation>高级选项</translation>
    </message>
    <message>
        <source>CRL (Revocation List): </source>
        <translation>CRL (撤销列表): </translation>
    </message>
    <message>
        <source>Invalid Hostnames: </source>
        <translation>无效主机名: </translation>
    </message>
    <message>
        <source>Not Allowed</source>
        <translation>不允许</translation>
    </message>
    <message>
        <source>Allowed</source>
        <translation>允许</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>错误</translation>
    </message>
    <message>
        <source>Error: </source>
        <translation>错误: </translation>
    </message>
    <message>
        <source> file does not exist</source>
        <translation> 文件不存在</translation>
    </message>
    <message>
        <source>CA-signed certificate</source>
        <translation>CA 签名证书</translation>
    </message>
    <message>
        <source>PEM Certificate/Key</source>
        <translation>PEM 证书/密钥</translation>
    </message>
    <message>
        <source>CRL (Revocation List)</source>
        <translation>CRL (撤销列表)</translation>
    </message>
    <message>
        <source>Choose File</source>
        <translation>选择文件</translation>
    </message>
    <message>
        <source> mongo --tlsCAFile : Certificate Authority file for TLS</source>
        <translation> mongo --tlsCAFile : 用于 TLS 的证书颁发机构 (CA) 文件</translation>
    </message>
    <message>
        <source> mongo --tlsCertificateKeyFile : PEM certificate/key file for TLS</source>
        <translation> mongo --tlsCertificateKeyFile : 用于 TLS 的 PEM 证书/密钥文件</translation>
    </message>
    <message>
        <source> mongo --tlsCertificateKeyFilePassword : Password for key in PEM file for TLS</source>
        <translation> mongo --tlsCertificateKeyFilePassword : 用于 TLS 的 PEM 文件中的密钥密码</translation>
    </message>
    <message>
        <source> mongo --tlsAllowInvalidHostnames : Allow connections to servers with non-matching hostnames</source>
        <translation> mongo --tlsAllowInvalidHostnames : 允许连接到主机名不匹配的服务器</translation>
    </message>
    <message>
        <source> mongo --tlsAllowInvalidCertificates : Allow connections to servers with invalid certificates</source>
        <translation> mongo --tlsAllowInvalidCertificates : 允许连接到证书无效的服务器</translation>
    </message>
    <message>
        <source> mongo --tlsCRLFile : Certificate Revocation List file for TLS</source>
        <translation> mongo --tlsCRLFile : 用于 TLS 的证书撤销列表 (CRL) 文件</translation>
    </message>
</context>
<context>
    <name>Robomongo::ConnectionBasicTab</name>
    <message>
        <source>Type:</source>
        <translation>类型:</translation>
    </message>
    <message>
        <source>Direct Connection</source>
        <translation>直接连接</translation>
    </message>
    <message>
        <source>Replica Set</source>
        <translation>副本集</translation>
    </message>
    <message>
        <source>Name:</source>
        <translation>名称:</translation>
    </message>
    <message>
        <source>Choose any connection name that will help you to identify this connection.</source>
        <translation>选择任何有助于您识别此连接的名称。</translation>
    </message>
    <message>
        <source>Address:</source>
        <translation>地址:</translation>
    </message>
    <message>
        <source>Specify host and port of MongoDB server. Host can be either IPv4, IPv6 or domain name.</source>
        <translation>指定 MongoDB 服务器的主机和端口。主机可以是 IPv4、IPv6 或域名。</translation>
    </message>
    <message>
        <source>Members:</source>
        <translation>成员:</translation>
    </message>
    <message>
        <source>Set Name:</source>
        <translation>集合名称:</translation>
    </message>
    <message>
        <source>Import connection details from MongoDB URI connection string</source>
        <translation>从 MongoDB URI 连接字符串导入连接详情</translation>
    </message>
    <message>
        <source>From URI</source>
        <translation>从 URI</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>错误</translation>
    </message>
    <message>
        <source>Replica set members cannot be empty. Please enter at least one member.</source>
        <translation>副本集成员不能为空。请输入至少一个成员。</translation>
    </message>
    <message>
        <source>Replica set member items must all contain ':' between hostname and port.</source>
        <translation>副本集成员项在主机名和端口之间必须包含 ':'。</translation>
    </message>
    <message>
        <source>Please remove duplicate member, two replica set members cannot have the same hostname and port.</source>
        <translation>请移除重复成员，两个副本集成员不能具有相同的主机名和端口。</translation>
    </message>
    <message>
        <source>New Connection</source>
        <translation>新建连接</translation>
    </message>
    <message>
        <source>MongoDB URI:
</source>
        <translation>MongoDB URI:
</translation>
    </message>
</context>
<context>
    <name>Robomongo::ConnectionAuthTab</name>
    <message>
        <source>Perform authentication</source>
        <translation>执行认证</translation>
    </message>
    <message>
        <source>&lt;nobr&gt;The admin database is unique in MongoDB.&lt;/nobr&gt; Users with normal access to the admin database have read and write access to &lt;b&gt;all databases&lt;/b&gt;.</source>
        <translation>&lt;nobr&gt;admin 数据库在 MongoDB 中是唯一的。&lt;/nobr&gt; 拥有 admin 数据库正常访问权限的用户对 &lt;b&gt;所有数据库&lt;/b&gt; 具有读写权限。</translation>
    </message>
    <message>
        <source>User Name</source>
        <translation>用户名</translation>
    </message>
    <message>
        <source>Auth Mechanism</source>
        <translation>认证机制</translation>
    </message>
    <message>
        <source>Password</source>
        <translation>密码</translation>
    </message>
    <message>
        <source>Database</source>
        <translation>数据库</translation>
    </message>
    <message>
        <source>Comma-separated e.g. products, users</source>
        <translation>以逗号分隔，例如 products, users</translation>
    </message>
    <message>
        <source>Databases</source>
        <translation>数据库</translation>
    </message>
    <message>
        <source>Some MongoDB users might not have the permission to get the list of database names (&lt;b&gt;listDatabases&lt;/b&gt; command). For this case, manually add the name of the database(s) that this user has access to.</source>
        <translation>某些 MongoDB 用户可能没有获取数据库名称列表（&lt;b&gt;listDatabases&lt;/b&gt; 命令）的权限。在这种情况下，请手动添加该用户有权访问的数据库名称。</translation>
    </message>
    <message>
        <source>Manually specify visible databases</source>
        <translation>手动指定可见的数据库</translation>
    </message>
</context>
<context>
    <name>Robomongo::SSLTab</name>
    <message>
        <source> mongo --tlsCAFile : Certificate Authority file for TLS</source>
        <translation> mongo --tlsCAFile : 用于 TLS 的证书颁发机构 (CA) 文件</translation>
    </message>
    <message>
        <source> mongo --tlsCertificateKeyFile : PEM certificate/key file for TLS</source>
        <translation> mongo --tlsCertificateKeyFile : 用于 TLS 的 PEM 证书/密钥文件</translation>
    </message>
    <message>
        <source> mongo --tlsCertificateKeyFilePassword : Password for key in PEM file for TLS</source>
        <translation> mongo --tlsCertificateKeyFilePassword : 用于 TLS 的 PEM 文件中的密钥密码</translation>
    </message>
    <message>
        <source> mongo --tlsAllowInvalidHostnames : Allow connections to servers with non-matching hostnames</source>
        <translation> mongo --tlsAllowInvalidHostnames : 允许连接到主机名不匹配的服务器</translation>
    </message>
    <message>
        <source> mongo --tlsAllowInvalidCertificates : Allow connections to servers with invalid certificates</source>
        <translation> mongo --tlsAllowInvalidCertificates : 允许连接到证书无效的服务器</translation>
    </message>
    <message>
        <source> mongo --tlsCRLFile : Certificate Revocation List file for TLS</source>
        <translation> mongo --tlsCRLFile : 用于 TLS 的证书撤销列表 (CRL) 文件</translation>
    </message>
    <message>
        <source>Use TLS protocol</source>
        <translation>使用 TLS 协议</translation>
    </message>
    <message>
        <source>Authentication Method: </source>
        <translation>认证方法: </translation>
    </message>
    <message>
        <source>Self-signed Certificate</source>
        <translation>自签名证书</translation>
    </message>
    <message>
        <source>Use CA Certificate</source>
        <translation>使用 CA 证书</translation>
    </message>
    <message>
        <source>In general, avoid using self-signed certificates unless the network is trusted. If self-signed certificate is used, the communications channel will be encrypted however there will be no validation of server identity.</source>
        <translation>通常情况下，除非网络是受信任的，否则请避免使用自签名证书。如果使用自签名证书，通信通道将被加密，但不会验证服务器身份。</translation>
    </message>
    <message>
        <source>CA Certificate:</source>
        <translation>CA 证书:</translation>
    </message>
    <message>
        <source>Use PEM Cert./Key: </source>
        <translation>使用 PEM 证书/密钥: </translation>
    </message>
    <message>
        <source>Enable this option to connect to a MongoDB that requires CA-signed client certificates/key file.</source>
        <translation>启用此选项以连接到需要 CA 签名客户端证书/密钥文件的 MongoDB。</translation>
    </message>
    <message>
        <source>PEM Certificate/Key: </source>
        <translation>PEM 证书/密钥: </translation>
    </message>
    <message>
        <source>Passphrase: </source>
        <translation>密码短语: </translation>
    </message>
    <message>
        <source>Ask for passphrase each time</source>
        <translation>每次询问密码短语</translation>
    </message>
    <message>
        <source>Advanced Options</source>
        <translation>高级选项</translation>
    </message>
    <message>
        <source>CRL (Revocation List): </source>
        <translation>CRL (撤销列表): </translation>
    </message>
    <message>
        <source>Invalid Hostnames: </source>
        <translation>无效主机名: </translation>
    </message>
    <message>
        <source>Not Allowed</source>
        <translation>不允许</translation>
    </message>
    <message>
        <source>Allowed</source>
        <translation>允许</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>错误</translation>
    </message>
    <message>
        <source>Error: </source>
        <translation>错误: </translation>
    </message>
    <message>
        <source> file does not exist</source>
        <translation> 文件不存在</translation>
    </message>
    <message>
        <source>CA-signed certificate</source>
        <translation>CA 签名证书</translation>
    </message>
    <message>
        <source>PEM Certificate/Key</source>
        <translation>PEM 证书/密钥</translation>
    </message>
    <message>
        <source>CRL (Revocation List)</source>
        <translation>CRL (撤销列表)</translation>
    </message>
    <message>
        <source>Choose File</source>
        <translation>选择文件</translation>
    </message>
</context>
<context>
    <name>Robomongo::SSHTunnelTab</name>
    <message>
        <source>Ask for password each time</source>
        <translation>每次询问密码</translation>
    </message>
    <message>
        <source>Ask for passphrase each time</source>
        <translation>每次询问密码短语</translation>
    </message>
    <message>
        <source>Use SSH tunnel</source>
        <translation>使用 SSH 隧道</translation>
    </message>
    <message>
        <source>Password</source>
        <translation>密码</translation>
    </message>
    <message>
        <source>Private Key</source>
        <translation>私钥</translation>
    </message>
    <message>
        <source>DSA, RSA, and on Windows/macOS ECDSA, Ed25519 keys are supported. PPK keys must be converted to OPENSSH format.</source>
        <translation>支持 DSA, RSA, 以及在 Windows/macOS 上的 ECDSA, Ed25519 密钥。PPK 密钥必须转换为 OPENSSH 格式。</translation>
    </message>
    <message>
        <source>User Password:</source>
        <translation>用户密码:</translation>
    </message>
    <message>
        <source>Private key:</source>
        <translation>私钥:</translation>
    </message>
    <message>
        <source>Passphrase:</source>
        <translation>密码短语:</translation>
    </message>
    <message>
        <source>SSH Address:</source>
        <translation>SSH 地址:</translation>
    </message>
    <message>
        <source>SSH User Name:</source>
        <translation>SSH 用户名:</translation>
    </message>
    <message>
        <source>SSH Auth Method:</source>
        <translation>SSH 认证方式:</translation>
    </message>
    <message>
        <source>SSH is currently not supported for Replica Set connections</source>
        <translation>目前副本集连接不支持 SSH</translation>
    </message>
    <message>
        <source>Select private key file</source>
        <translation>选择私钥文件</translation>
    </message>
    <message>
        <source>Private key files (*)</source>
        <translation>私钥文件 (*)</translation>
    </message>
    <message>
        <source>Private key file "%1" doesn't exist</source>
        <translation>私钥文件 "%1" 不存在</translation>
    </message>
    <message>
        <source>Settings are incomplete</source>
        <translation>设置不完整</translation>
    </message>
</context>
<context>
    <name>Robomongo::ConnectionAdvancedTab</name>
    <message>
        <source>Database, that will be default (&lt;code&gt;db&lt;/code&gt; shell variable will point to this database). By default, default database will be the one you authenticate on, or &lt;code&gt;test&lt;/code&gt; otherwise. Leave this field empty, if you want default behavior.</source>
        <translation>将作为默认数据库（&lt;code&gt;db&lt;/code&gt; Shell 变量将指向此数据库）。默认情况下，默认数据库将是您进行身份验证的数据库，否则为 &lt;code&gt;test&lt;/code&gt;。如果您希望使用默认行为，请将此字段留空。</translation>
    </message>
    <message>
        <source>Default Database:</source>
        <translation>默认数据库:</translation>
    </message>
</context>
</TS>